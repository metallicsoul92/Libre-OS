#include "../include/internal.h"
#include "../include/kernel.h"
#include "../include/multiboot.h"
#include "../include/tty.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isr.h"
#include "../include/paging.h"
/**
* Kernel Information
*/

 _internal_kernel_info _kInfo = {{"Libre-OS","Alpha"} , {0,0,1,0}};

/**
*Multiboot Information
*/
	multiboot_info_t *mbt;

uint32_t kernel_begin;
uint32_t kernel_end;

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

 int intTest = 45;

//Other Functions here
  printk("Welcome to %s\nVersion: %s\n",_kInfo.name.name,_kInfo.name.versionName);
  printk("Multiboot Flags: 0x%x\n",mbt->flags);
  printk("Multiboot addr : 0x%x\n", addr);
  printk("Multiboot Memory Low: 0x%x\nMultiboot Memory Upper: 0x%x\n",mbt->mem_lower,mbt->mem_upper);
  printk("Multiboot mmap address: 0x%x\n",mbt->mmap_addr);
  printk("Multiboot mod count : %u\nMod Address: 0x%x\n",mbt->mods_count, mbt->mods_addr);
  printk("=====================================\n");
  printk("Global Descriptor Installed...\n");
  printk("Interupt Descriptor Installed...\n");
  printk("Interupt Request Queue Installed...\n");
  printk("Address of beginning of kernel : 0x%x\n", &kernel_begin);
  printk("Address of end of kernel: 0x%x\n", &kernel_end);
    return 0;
}
