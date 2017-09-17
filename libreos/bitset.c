#include "../include/libreos/bitset.h"
#include "../include/kmem.h"

bitset bitsetCreate(uint8_t info){
  union {
    bitset b;
    uint8_t u8;
  } un;

  un tmp;
  tmp.u8 = info;

  return tmp.b;
}
bitset bitsetCreateFromOther(bitset info){
  return info;
}
bitset * bitsetMalloc(){
  //this is a kernel based header for now so it will use kmalloc
  bitset *b = (bitset *)kmalloc(sizeof(bitset*));

  return b;

}
bitset * bitsetInit(uint8_t info){
  bitset * tmp = bitsetMalloc();
  *tmp = bitsetCreate(info);

  return tmp;
}


//Reverse the bitset,
bitset bitsetReverse(bitset *bits){
  bitset tmp;

  tmp.b1 = bits->b8;
  tmp.b2 = bits->b7;
  tmp.b3 = bits->b6;
  tmp.b4 = bits->b5;
  tmp.b5 = bits->b4;
  tmp.b6 = bits->b3;
  tmp.b7 = bits->b2;
  tmp.b8 = bits->b1;

  return tmp;
}
bitset * bitsetPtrReverse(bitset * bits){
  bitset * tmp;

  tmp.b1 = bits->b8;
  tmp.b2 = bits->b7;
  tmp.b3 = bits->b6;
  tmp.b4 = bits->b5;
  tmp.b5 = bits->b4;
  tmp.b6 = bits->b3;
  tmp.b7 = bits->b2;
  tmp.b8 = bits->b1;

  return tmp;
}



// These will all return ints incase failure happens:
int bitsetCopy(bitset *source, bitset *destination ){
  //figure out the best way to handle this?
  if(destination == NULL){
    return -1;
  }else if(source == NULL){
    return -2;
  }else
  destination = source;
  return 0;
}
int bitsetMove(bitset *source,bitset *destination ){
  //figure out the best way to handle this?
  if(destination == NULL){
    return -1;
  }else if(source == NULL){
    return -2;
  }else
  destination = source;
  source = NULL;
  return 0;
}
int bitsetSwap(bitset *first, bitset *second){
  const bitset * f = first;
  const bitset * s = second;

  bitset * tmp = first;
  first = second;
  second = tmp;

  if(second == s){
    return -1;
  }else if(first == f){
    return -2;
  }else
  return 0;
}
int bitsetSetBit(bitset * source,uint8_t index, uint8_t data){
  switch(index){
    case 0:
    source.b1=data;
    break;
    case 1:
    source.b2=data;
    break;
    case 2:
    source.b3=data;
    break;
    case 3:
    source.b4=data;
    break;
    case 4:
    source.b5=data;
    break;
    case 5:
    source.b6=data;
    break;
    case 6:
    source.b7=data;
    break;
    case 7:
    source.b8=data;
    break;
  }
  return 0;
}

uint8_t fromBitset(bitset info){
  return info.b8 + (info.b7 * 2)+ (info.b6 * 4)+ (info.b5 * 8)
  + (info.b4 * 16)+ (info.b3 * 32)+ (info.b2 * 64)+ (info.b1 * 128);
}
uint8_t fromBitsetPtr(bitset *info){
  return info->b8 + (info->b7 * 2)+ (info->b6 * 4)+ (info->b5 * 8)
  + (info->b4 * 16)+ (info->b3 * 32)+ (info->b2 * 64)+ (info->b1 * 128);
}
