#include "../include/internal.h"
#include "../include/kernel.h"
#include "../include/multiboot.h"
#include "../include/tty.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isr.h"
#include "../include/kbd.h"
#include "../include/paging.h"
#include "../include/cpufeatures.h"
/**
* Kernel Information
*/

 _internal_kernel_info _kInfo = {{"Libre-OS","Alpha"} , {0,0,1,0}};

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
 // initializePaging();


//Other Functions here
  printk("Welcome to %s\nVersion: %s\n",_kInfo.name.name,_kInfo.name.versionName);
  printk("Multiboot Flags: 0x%x\n",mbt->flags);
  printk("Multiboot addr : 0x%x\n", addr);
  printk("Multiboot Memory Low: 0x%x\nMultiboot Memory Upper: 0x%x\n",mbt->mem_lower,mbt->mem_upper);
  printk("Multiboot mmap address: 0x%x\n",mbt->mmap_addr);
  printk("Multiboot mod count : %u\nMod Address: 0x%x\n",mbt->mods_count, mbt->mods_addr);
  printk("=====================================\n");
  unsigned int cpuidret[4] = {0,0,0,0};
  __get_cpuid(0,&cpuidret[0],&cpuidret[1],&cpuidret[2],&cpuidret[3]);
  char vendorString[12];
  getVendorString(vendorString,cpuidret[1],cpuidret[2],cpuidret[3]);
  printk("CPUID 0 RESULTS     : EAX(%x),EBX(%x)\n",cpuidret[0],cpuidret[1]);
  printk("                      ECX(%x),EDX(%x)\n\n",cpuidret[0],cpuidret[1]);
  printk("CPUID 0 VENDOR STRING : %s%\n",vendorString);
  cpuidret[0] =1;
  __get_cpuid(0,&cpuidret[0],&cpuidret[1],&cpuidret[2],&cpuidret[3]);
  char cpuidFeats[150];
  memset(cpuidFeats,0,sizeof(cpuidFeats));
  featureString(cpuidFeats,cpuidret[2],cpuidret[3]);
  printk("CPU FEATURES:\n%s\n",cpuidFeats);
  printk("=====================================\n");
  printk("Global Descriptor Installed...\n");
  printk("Interupt Descriptor Installed...\n");
  printk("Interupt Request Queue Installed...\n");
  while(1){
  keyboard_handler_main();
}
    return 0;
}
