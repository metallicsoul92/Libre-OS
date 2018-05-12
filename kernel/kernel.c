#include "../include/internal.h"
#include "../include/multiboot.h"
#include "../include/tty.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isr.h"
#include "../include/kbd.h"
#include "../include/kmem.h"
#include "../include/paging.h"
#include "../include/cpufeatures.h"
#include "../include/task.h"
#include "../libc/include/string.h"
#include "../include/drivers/ata.h"
/**
* Kernel Information
*/

 _internal_kernel_info _kInfo = {{"Libre-OS","Alpha"} , {0,0,1,0}};
 _cpuidProf cpuidProf;
 _vmmu vmmu;

char versionString[32];
 void generateVersionString(_internal_kernel_version * v){
   const char * vInfo[4] = {STR(v.maj),STR(v.min),
                           STR(v.bug),STR(v.tweak)};
                   memset(versionString,0,sizeof(versionString));
                   strcat(vInfo[0],versionString);
                   strcat(".",versionString);
                   strcat(vInfo[1],versionString);
                   strcat(".",versionString);
                   strcat(vInfo[2],versionString);
                   strcat(".",versionString);
                   strcat(vInfo[3],versionString);
                   strcat(".",versionString);
}
/**
*Multiboot Information
*/
	multiboot_info_t *mbt;

int kernel_main(unsigned long magic, unsigned long addr){

//Pre-Boot Shit
  if(magic != MULTIBOOT_BOOTLOADER_MAGIC){
    printk("Error Multiboot magic invalid");
  }

  mbt =(multiboot_info_t *) addr;

//Initialization here
 initializeTerminal();
 gdt_install();
 	idt_install();
 	isrs_install();
 	irq_install();
//  initializePaging();
//  setupBasicPaging();
//

unsigned int cpuidret[4] = {0,0,0,0};
__get_cpuid(0,&cpuidret[0],&cpuidret[1],&cpuidret[2],&cpuidret[3]);
char vendorString[12];
getVendorString(vendorString,cpuidret[1],cpuidret[2],cpuidret[3]);

//Other Functions here
  printk("Welcome to %s     Version: %s\n",_kInfo.name.name,_kInfo.name.versionName);
  printk("Multiboot Flags: 0x%x\n",mbt->flags);
  printk("Multiboot addr : 0x%x\n", addr);
  printk("Multiboot Memory Low: 0x%x\nMultiboot Memory Upper: 0x%x\n",mbt->mem_lower,mbt->mem_upper);
  printk("Multiboot mmap address: 0x%x\n",mbt->mmap_addr);
  printk("Multiboot mod count : %u\nMod Address: 0x%x\n",mbt->mods_count, mbt->mods_addr);
  printk("=====================================\n");
  printk("CPUID 0 RESULTS     : EAX(%x),EBX(%x),ECX(%x),EDX(%x)\n",cpuidret[0],cpuidret[1],cpuidret[2],cpuidret[3]);
  printk("CPUID 0 VENDOR STRING : %s%\n",vendorString);
  cpuidret[0]=1;
  __get_cpuid(0,&cpuidret[0],&cpuidret[1],&cpuidret[2],&cpuidret[3]);
  cpuidProf.ecx = cpuidret[2];
  cpuidProf.edx = cpuidret[3];
  char cpuidFeats[1024];
  memset(&cpuidFeats,0,sizeof(cpuidFeats));
  featureString(cpuidFeats,cpuidret[2],cpuidret[3]);
  printk("CPU FEATURES:\n%s\n",cpuidFeats);
  printk("=====================================\n");
  printk("Global Descriptor Installed...     Interupt Descriptor Installed...\n");
  printk("Interupt Request Queue Installed...\n");
  initMem(&vmmu,mbt);
  paging_init();
  initTasking();
  ata_init();


  while(1){
  keyboard_handler_main();
}
    return 0;
}
