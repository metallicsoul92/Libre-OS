#include "../include/stdlib.h"
#include "../include/string.h"
#include "../../include/kmem.h"


void *malloc(size_t sz){
  #if defined(__is_libk)
    return vm_allocate(sz,KA);
  #else
    return vm_allocate(sz,UA);
  #endif
}
void *calloc(size_t num,size_t sz){
  void *address;
  #if defined(__is_libk)
    address = vm_allocate(sz,KA);
  #else
    address = vm_allocate(sz,UA);
  #endif

  memset(address,0,sz);

  return address;

}
//This is just gonna reallocate , and not even try to merge
void *realloc(void *address, size_t sz){
  vm_entry_t * temp = addressToEntry(address);
  void *newAddress;

  #if defined(__is_libk)
    newAddress = vm_allocate(sz,KA);
  #else
    newAddress = vm_allocate(sz,UA);
  #endif
    memcpy(address,newAddress,temp->size);

    vm_entry_t *newTemp = addressToEntry(newAddress);
    vm_entry_t *prevAdd = prevEntry(temp);
    prevAdd->next = newTemp;
    newTemp->next = prevAdd->next;
    vm_entry_free(temp);

    return newAddress;

}
void free(void *address){
  vm_entry_free(address);
}
