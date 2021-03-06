#include "../include/cpufeatures.h"


void getVendorString(char * output,unsigned int ebx,unsigned int ecx,unsigned int edx){
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


const char *__featECX[32]={
  "SSE3", "PCLMUL","DTES64","MONITOR",
  "DS-CPL","VMX","SMX","EST","TM2",
  "SSSE3","CNXT-ID","SDBG","FMA","CX16",
  "XPTR","PDCM","(reserved)","PCID","DCA",
  "SSE4-1","SSE4.2","X2APIC","MOVBE","POPCNT",
  "TSC-DL","AES","XSAVE","OSXSAVE","AVX","F16C",
  "RDRND","HYPER-V"
};

const char *__featEDX[32]={
  "FPU","VME","DE","PSE","TSC",
  "MSR","PAE","MCE","CMPXCHG8B",
  "APCI","(res bit)","SEP",
  "MTRR","PGE","MCA", "CMOV", "PAT",
  "PSE-36","PSN","CLFLUSH","(res bit)",
  "DS","ACPI-THERM","MMX","FXSAVE","SSE",
  "SSE2","SS","HTT","THERM","IA64","PBE"
};



void featureString(char * output,uint32_t ecx, uint32_t edx){


  for(int i = 0; i < 32; i++){

       if(ecx & (1 << i)){
         strcat(output,__featECX[i]);
         if(i == 30){
         }else{
           strcat(output,",");
         }
       }
  }

  strcat(output,"\n");

  for(int n = 0; n < 32; n++){
  if(edx & (1 << n)){
    strcat(output,__featEDX[n]);
    if(n == 30){
    }else{
      strcat(output,",");
    }
  }
}

}
