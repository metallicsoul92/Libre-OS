#include "../include/config.h"
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
#include "../include/drivers/fs/vfs/vfs.h"
/**
* Kernel Information
*/
 _internal_kernel_info _kInfo = {{"Libre-OS",VERSIONSTRING} ,
                                {VERSIONMAJOR,VERSIONMINOR,
                                  VERSIONBUG,VERSIONTWEAK} ,
                                  NULL};
 _cpuidProf cpuidProf;
 _vmmu vmmu;

fs_t initVFS;

char versionString[32];
 void generateVersionString(_internal_kernel_version * v){
   const char * vInfo[4] = {STR(v.maj),STR(v.min),
                           STR(v.bug),STR(v.tweak)};
                   memset(versionString,0,sizeof(versionString));
                   strcat(versionString,vInfo[0]);
                   strcat(versionString,".");
                   strcat(versionString,vInfo[1]);
                   strcat(versionString,".");
                   strcat(versionString,vInfo[2]);
                   strcat(versionString,".");
                   strcat(versionString,vInfo[3]);
                   strcat(versionString,".");
}
/**
*Multiboot Information
*/
	multiboot_info_t *mbt;

int kernel_main(unsigned long magic, unsigned long addr){


  //Initialization here
   initializeTerminal();

//Pre-Boot Shit
  if(magic != MULTIBOOT_BOOTLOADER_MAGIC){
    printk("Error Multiboot magic invalid\n");
    printk("Expected %u : Result : %u\n",MULTIBOOT_BOOTLOADER_MAGIC,magic);
  }

  mbt =(multiboot_info_t *) addr;

//More Initialization here
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
  detectArch(&_kInfo);
  printk("Architecture : %s\n", _kInfo.archType);
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
  printk("VMMU Memory maps : %d\n",vmmu.availableMemAmount);
  for(unsigned int i = 0; i < vmmu.availableMemAmount;i++){
  printk("Memory Map #%d : Address : %X  Size: %U\n",
            i,vmmu.availAddrStart[i],vmmu.availAddrSize[i]);
  }
  vfsInit();
  initVFS.name = "Kernel Virtual FS";
  vfsInstall(&initVFS);
  //ata_init();




  while(1){
  keyboard_handler_main();
}
    return 0;
}
