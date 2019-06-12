#include <getopt.h>
#include <stdlib.h>
#include "IFrService.h"

#include "fr.h"

void Init() {

}

int main(int argc, char* argv[]) {
  // Initialize
  Init();
  printf("face recognition client\n");
  sp < IServiceManager > sm = defaultServiceManager();
  sp < IBinder > binder = sm->getService(String16("service.frservice"));
  sp<IFrService> cs = interface_cast < IFrService > (binder);
  cs->sayHello();
  return 0;
}
