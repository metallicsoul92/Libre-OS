#include "../../../include/drivers/exec/elf/elf.h"

//Based off AdeRegt's SanderOSUSB : https://github.com/AdeRegt/SanderOSUSB/blob/master/kernel/exec/elf.c

int isELF(uint8_t * elf){
  return (elf[0]==ELFMAG0 && elf[1]==ELFMAG1 &&
          elf[2]==ELFMAG2 && elf[3] == ELFMAG3);
}
unsigned long loadELF(void * elf){
#ifdef __IX86__
  Elf32_Ehdr * header = (Elf32_Ehdr*)elf;
  if(header->e_type == 2){
    Elf32_Shdr * sections = (Elf_Shdr *)((long)elf + helf->e_shoff);

    for(unsigned int i = 0;i < header->e_shnum; i++){
      Elf32_Shdr section = sections[i];
      if(section.sh_addr){
        if(section.sh_type == 1){
          printf("ELF: Loading Segment at : %x\n",section.sh_addr);
          for(unsigned int j = 0; j < section.sh_size; j++){
          ((char*)section.sh_addr)[j] = ((char*)elf + section.sh_offset)[e];
          }
        }else{
          printf("ELF:Not Copying Segment.\n");
        }
      }else{
        printf("ELF: Skipping %x , No Location.\n", i);
      }
    }
    printf("ELF: Ready at %x\n",header->e_entry);
    return header->e_entry;
  }else{
    printf("Error: Unknown ELF Format";);
  }
  return 0;
#endif
}
