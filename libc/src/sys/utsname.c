#include "../../include/sys/utsname.h"
#include "../../../include/internal.h"
#include "../../include/stddef.h"

int uname(utsname_t *name){
  #ifdef __is_libk
  extern char versionString[32];
  name->sysname = _kInfo.name.name;
  name->nodename = NULL; //idk what to put here yet
  generateVersionString(&_kInfo.version);
  name->release = _kInfo.name.versionName;
  name->version = versionString;
  //TODO: When cross compiling, check here if building for specific
  //architectures . For now i will just set it to the address of x86 string
  name->machine = (char*)&archList[0];
  #else
  //this will probably be stored on a filesystem somewhere
  //ill have it check there eventually
  return -1; // todo fix this
  #endif

  return -2; //if it gets here there is a problem
}
