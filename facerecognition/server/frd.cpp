#include <getopt.h>
#include <stdlib.h>
#include "IFrService.h"
#include "frd.h"

#include <camera/Camera.h>
#include <gui/BufferItemConsumer.h>
#include <gui/IGraphicBufferProducer.h>
#include <gui/Surface.h>
#include <gui/CpuConsumer.h>

using namespace android;

struct DummyConsumer : public BnConsumerListener {
  virtual void onFrameAvailable(const BufferItem& /* item */) {
    printf("onFrameAvailable");
  }

  virtual void onBuffersReleased() {
    printf("onBuffersReleased");
  }

  virtual void onSidebandStreamChanged() {
    printf("onSidebandStreamChanged");
  }
};

struct FrameListener : public ConsumerBase::FrameAvailableListener {

  FrameListener() {
      mPendingFrames = 0;
  }

  // CpuConsumer::FrameAvailableListener implementation
  virtual void onFrameAvailable(const BufferItem& /* item */) {
      printf("Frame now available (start)");

      Mutex::Autolock lock(mMutex);
      mPendingFrames++;
      mCondition.signal();

      printf("Frame now available (end)");
  }

  status_t waitForFrame(nsecs_t timeout) {
      status_t res;
      Mutex::Autolock lock(mMutex);
      while (mPendingFrames == 0) {
          res = mCondition.waitRelative(mMutex, timeout);
          if (res != OK) return res;
      }
      mPendingFrames--;
      return OK;
  }

private:
    Mutex mMutex;
    Condition mCondition;
    int mPendingFrames;
};

void Init() {

}

int main(int argc, char* argv[]) {
  // Initialize
  Init();
  printf("face recognition server\n");
  //sp < IServiceManager > sm = defaultServiceManager();
  //sm->addService(String16("service.frservice"), new BnFrService());

  String16 package("gonk.camera");

  fprintf(stderr,"opening cam\n");

  sp<Camera> cam = Camera::connect(0,package,BnCameraService::USE_CALLING_UID);

  if(cam!=NULL){
    fprintf(stderr,"cam opened\n");
  } else {
    fprintf(stderr,"cam not opened\n");
    return 0;
  }

  android::String8    params= cam->getParameters();
  printf("cam opened  params: %s\n", params.string());

  sp<IGraphicBufferProducer> gbProducer;
  sp<IGraphicBufferConsumer> gbConsumer;
  BufferQueue::createBufferQueue(&gbProducer, &gbConsumer);
  sp<BufferItemConsumer> opaqueConsumer = new BufferItemConsumer(gbConsumer,
                  GRALLOC_USAGE_SW_READ_NEVER, /*maxImages*/2, /*controlledByApp*/true);
  gbConsumer->setDefaultBufferSize(640, 480);
  gbConsumer->setDefaultBufferFormat(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED);

  sp<Surface> surface(new Surface(gbProducer, /*controlledByApp*/false));

  sp<DummyConsumer> dc(new DummyConsumer);
  gbConsumer->consumerConnect(dc, false);

  android::sp<CpuConsumer> mCpuConsumer;
  mCpuConsumer = new CpuConsumer(gbConsumer, 1);
  mCpuConsumer->setName(String8("CameraStreamTest::mCpuConsumer"));

  sp<FrameListener> frameListener;
  frameListener = new FrameListener();
  mCpuConsumer->setFrameAvailableListener(frameListener);

  cam->setPreviewTarget(gbProducer);
  printf("previewEnabled:%d\n",cam->previewEnabled());
  printf("startPreview\n");
  int ret = cam->startPreview();

  cam->stopPreview();
  printf("cam stopPreview\n");

  //ProcessState::self()->startThreadPool();
  //IPCThreadState::self()->joinThreadPool();

  return 0;
}