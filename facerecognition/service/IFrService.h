#ifndef FR_SERVICE_DEMO
#define FR_SERVICE_DEMO
#include <stdio.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

using namespace android;
namespace android
{
  class IFrService : public IInterface
  {
  public:
    DECLARE_META_INTERFACE(FrService);
    virtual void sayHello() = 0;
  };


  enum
  {
    HELLO = 1,
  };


  class BpFrService: public BpInterface<IFrService> {
  public:
    BpFrService(const sp<IBinder>& impl);
    virtual void sayHello();
  };

  class BnFrService: public BnInterface<IFrService> {
  public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,
      uint32_t flags = 0);
    virtual void sayHello();
  };
}
#endif
