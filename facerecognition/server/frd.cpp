#include <getopt.h>
#include <stdlib.h>
#include "IFrService.h"

#include "frd.h"

void Init() {

}

int main(int argc, char* argv[]) {
  // Initialize
  Init();
  printf("face recognition server\n");
  sp < IServiceManager > sm = defaultServiceManager();
  sm->addService(String16("service.frservice"), new BnFrService());
  ProcessState::self()->startThreadPool();
  IPCThreadState::self()->joinThreadPool();
  return 0;
}
