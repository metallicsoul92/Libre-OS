#ifndef BITSET_H_
#define BITSET_H_

#include "../../libc/include/sys/cdefs.h"

struct _bitset{
  uint8_t b1:1;
  uint8_t b2:1;
  uint8_t b3:1;
  uint8_t b4:1;
  uint8_t b5:1;
  uint8_t b6:1;
  uint8_t b7:1;
  uint8_t b8:1;
};

typedef struct _bitset bitset;

/*
These will be used to create bitsets
*/
bitset bitsetCreate(uint8_t info);
bitset bitsetCreateFromOther(bitset info);
bitset * bitsetMalloc();
bitset * bitsetInit(uint8_t info);


//Reverse the bitset,
bitset bitsetReverse(bitset *bits);
bitset * bitsetPtrReverse(bitset * bits);



// These will all return ints incase failure happens:
int bitsetCopy(bitset *source, bitset *destination );
int bitsetMove(bitset *source,bitset *destination );
int bitsetSwap(bitset *first, bitset *second);
int bitsetSetBit(bitset * source,uint8_t index, uint8_t data);

uint8_t fromBitset(bitset info);
uint8_t fromBitsetPtr(bitset *info);


#endif
