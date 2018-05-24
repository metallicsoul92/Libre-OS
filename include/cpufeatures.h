#ifndef CPUFEATURES_H_
#define CPUFEATURES_H_

#include "../libc/include/cpuid.h"
#include "../libc/include/string.h"

#ifndef HAS_CDEFS
#include "../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif

union _uinttochar{
  unsigned int ui;
  char ch[4];
};

typedef union _uinttochar uitoc;

struct __internal_cpuid{
    uint32_t ecx;
    uint32_t edx;
};

typedef struct __internal_cpuid _cpuidProf;

void getVendorString(char * output,unsigned int ebx,unsigned int ecx,unsigned int edx);

//NOTE output MUST BE an Empty String
void featureString(char * output,uint32_t ecx, uint32_t edx);



//const char * __cpu_vendorID[12];






#endif
