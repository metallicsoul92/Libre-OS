#ifndef CPUFEATURES_H_
#define CPUFEATURES_H_

#include "../libc/include/cpuid.h"
#include "../libc/include/sys/cdefs.h"
#include "../libc/include/string.h"

union _uinttochar{
  unsigned int ui;
  char ch[4];
};

typedef union _uinttochar uitoc;

inline void getVendorString(char * output,unsigned int ebx,unsigned int ecx,unsigned int edx){
  uitoc  convert[3];
  convert[0].ui =ebx;
  convert[1].ui =edx;
  convert[2].ui =ecx;

  output[0] = convert[0].ch[0];
  output[1] = convert[0].ch[1];
  output[2] = convert[0].ch[2];
  output[3] = convert[0].ch[3];
  output[4] = convert[1].ch[0];
  output[5] = convert[1].ch[1];
  output[6] = convert[1].ch[2];
  output[7] = convert[1].ch[3];
  output[8] = convert[2].ch[0];
  output[9] = convert[2].ch[1];
  output[10] = convert[2].ch[2];
  output[11] = convert[2].ch[3];
}
const char *__featECX[16]={
  "SSE3", "PCLMUL","LZCNT","SSSE3",
  "FMA", "CMPXCHG16B", "SSE4_1","SSE4_2",
  "MOVBE","POPCNT","AES","XSAVE","OSXAVE",
  "AVX","F16C","RDRND"
};

const char *__featEDX[6]={
  "CMPXCHG8B","CMOV","MMX","FXSAVE","SSE","SSE2"
};

//NOTE output MUST BE an Empty String
inline void featureString(char * output,uint32_t ecx, uint32_t edx){
  if(ecx & bit_SSE3){
    strcat(__featECX[0],output);
    strcat(",",output);
  }

  if(ecx & bit_PCLMUL){
    strcat(__featECX[1],output);
    strcat(",",output);
  }

  if(ecx & bit_LZCNT){
    strcat(__featECX[2],output);
    strcat(",",output);
  }

  if(ecx & bit_SSSE3){
    strcat(__featECX[3],output);
    strcat(",",output);
  }
  if(ecx & bit_FMA){
    strcat(__featECX[4],output);
    strcat(",",output);
  }

  if(ecx & bit_CMPXCHG16B){
    strcat(__featECX[5],output);
    strcat(",",output);
  }

  if(ecx & bit_SSE4_1){
    strcat(__featECX[6],output);
    strcat(",",output);
  }

  if(ecx & bit_SSE4_2){
    strcat(__featECX[7],output);
    strcat(",",output);
  }
  if(ecx & bit_MOVBE){
    strcat(__featECX[8],output);
    strcat(",",output);
  }

  if(ecx & bit_POPCNT){
    strcat(__featECX[9],output);
    strcat(",",output);
  }

  if(ecx & bit_AES){
    strcat(__featECX[10],output);
    strcat(",",output);
  }

  if(ecx & bit_XSAVE){
    strcat(__featECX[11],output);
    strcat(",",output);
  }
  if(ecx & bit_OSXSAVE){
    strcat(__featECX[12],output);
    strcat(",",output);
  }

  if(ecx & bit_AVX){
    strcat(__featECX[13],output);
    strcat(",",output);
  }

  if(ecx & bit_F16C){
    strcat(__featECX[14],output);
    strcat(",",output);
  }

  if(ecx & bit_RDRND){
    strcat(__featECX[15],output);
    strcat(",",output);
  }

  strcat("\n",output);

  if(edx & bit_CMPXCHG8B){
    strcat(__featEDX[0],output);
    strcat(",",output);
  }

  if(edx & bit_CMOV){
    strcat(__featEDX[1],output);
    strcat(",",output);
  }

  if(edx & bit_MMX){
    strcat(__featEDX[2],output);
    strcat(",",output);
  }

  if(edx & bit_FXSAVE){
    strcat(__featEDX[3],output);
    strcat(",",output);
  }

  if(edx & bit_SSE){
    strcat(__featEDX[4],output);
    strcat(",",output);
  }

  if(edx & bit_SSE2){
    strcat(__featEDX[5],output);
    strcat("\n",output);
  }

}


//const char * __cpu_vendorID[12];






#endif
