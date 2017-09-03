#include "../include/internal.h"
#include "../include/kernel.h"
#include "../include/multiboot.h"
#include "../include/tty.h"
#include "../include/gdt.h"
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

 int intTest = 45;

//Other Functions here
  printk("Welcome to %s\nVersion: %s\n",_kInfo.name.name,_kInfo.name.versionName);
  printk("Printk Tests:\n");
  printk("intTest = %d , expected 45\n",intTest);
  printk("======================================\n");
  printk("Multiboot addr = 0x%x\n", addr);
  printk("Multiboot Memory Low: 0x%x\n Multiboot Memory Upper: 0x%x\n",mbt->mem_lower,mbt->mem_upper);
  printk("Global Descriptor Installed...");
    return 0;
}
