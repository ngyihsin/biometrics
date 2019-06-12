#include "IFrService.h"
namespace android
{
    IMPLEMENT_META_INTERFACE(FrService, "android.fr.IFrService");

  // Client
  BpFrService::BpFrService(const sp<IBinder>& impl) :
      BpInterface<IFrService>(impl) {
  }

  // Client side sayHello
  void BpFrService::sayHello() {
    printf("BpFrService::sayHello\n");
    Parcel data, reply;
    data.writeInterfaceToken(IFrService::getInterfaceDescriptor());
    remote()->transact(HELLO, data, &reply);
    printf("get num from BnMyService: %d\n", reply.readInt32());
  }

  // Server
  status_t BnFrService::onTransact(uint_t code, const Parcel& data,
      Parcel* reply, uint32_t flags) {
    switch (code) {
    case HELLO: {
      printf("BnFrService:: got the client hello\n");
      CHECK_INTERFACE(IFrService, data, reply);
      sayHello();
      reply->writeInt32(2015);
      return NO_ERROR;
    }
      break;
    default:
      break;
    }
    return NO_ERROR;
  }

  // Server side sayHello implementation.
  void BnFrService::sayHello() {
    printf("BnFrService::sayHello\n");
  };
}