#ifndef DRIVER_EXEC_PE_H_
#define DRIVER_EXEC_PE_H_

#include <stdint.h>

/*
  Contents of this header describe the PE file format that windows uses
*/

struct dos_header{
  char signature[2];
  int16_t lastSize;
  int16_t nBlocks;
  int16_t nreloc;
  int16_t hdrsize;
  int16_t minalloc;
  int16_t maxalloc;
  void *ss; //2 byte value
  void *sp; //2 byte value
  int16_t checksum;
  void *is; //2 byte value
  void *ip; //2 byte value
  int16_t relocpos;
  int16_t noverlay;
  int16_t reserved1[4];
  int16_t oem_id;
  int16_t oem_info;
  int16_t reserved2[10];
  int32_t e_lfanew; //offset to the 'PE\0\0' signature relative to the beginning of the file
};

typedef struct dos_header dos_header_t;

struct coffHeader{
  int16_t machine;
  int16_t numberOfSections;
  int32_t timeDateStamp;
  int32_t pointerToSymbolTable;
  int32_t numberOfSymbols;
  int16_t sizeOfOptionalHeader;
  int16_t characteristics;
};

typedef struct coffHeader coff_header_t;

//Machine Type
#define MACH_i386 0x14c
#define MACH_x64 0x8664
#define MACH_MIPS_R3000 0x162
#define MACH_MIPS_R10000 0x168
#define MACH_MIPS_LE_WCI_2 0x169
#define MACH_OALPHA_AXP
#define MACH_ALPHA_AXP 0x184
#define MACH_HITACHI_SH3 0x1a2
#define	MACH_HITACHI_SH3_DSP 0x1a3
#define	MACH_HITACHI_SH4 0x1a6
#define MACH_HITACHI_SH5 0x1a8
#define	MACH_ARM_LE 0x1c0
#define MACH_THUMB 0x1c2
#define	MACH_ARMV7 0x1c4
#define	MACH_MATSUSHITA_AM33 0x1d3
#define	MACH_PowerPC_LE 0x1f0
#define	MACH_PowerPC_FP 0x1f1
#define	MACH_IA64 0x200
#define	MACH_MIPS16 0x266
#define	MACH_MOTO68000 0x268
#define	MACH_ALPHA_AXP_64 0x284
#define	MACH_MIPS_FPU 0x366
#define	MACH_MIPS16_FPU 0x466
#define	MACH_EFI_BYTE_CODE 0xebc
#define	MACH_AMD64 0x8664
#define MACH_MITSUBISHI_M32R_LE 0x9041
#define	MACH_ARM64_LE 0xaa64
#define	MACH_CLR_MSIL 0xc0ee

//Image type
#define	IMAGE_FILE_RELOCS_STRIPPED 0x0001 	//Relocation information was stripped from file
#define	IMAGE_FILE_EXECUTABLE_IMAGE 0x0002 	//The file is executable
#define	IMAGE_FILE_LINE_NUMS_STRIPPED 0x0004 	//COFF line numbers were stripped from file
#define	IMAGE_FILE_LOCAL_SYMS_STRIPPED 0x0008 	//COFF symbol table entries were stripped from file
#define	IMAGE_FILE_AGGRESIVE_WS_TRIM 0x0010 	//Aggressively trim the working set(obsolete)
#define	IMAGE_FILE_LARGE_ADDRESS_AWARE 	0x0020 	//The application can handle addresses greater than 2 GB
#define	IMAGE_FILE_BYTES_REVERSED_LO 	0x0080 	//The bytes of the word are reversed(obsolete)
#define	IMAGE_FILE_32BIT_MACHINE 0x0100 	//The computer supports 32-bit words
#define	IMAGE_FILE_DEBUG_STRIPPED 0x0200 	//Debugging information was removed and stored separately in another file
#define	IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP 	0x0400 	//If the image is on removable media, copy it to and run it from the swap file
#define	IMAGE_FILE_NET_RUN_FROM_SWAP 	0x0800 	//If the image is on the network, copy it to and run it from the swap file
#define	IMAGE_FILE_SYSTEM 0x1000 	//The image is a system file
#define	IMAGE_FILE_DLL 0x2000 	//The image is a DLL file
#define	IMAGE_FILE_UP_SYSTEM_ONLY 0x4000 	//The image should only be ran on a single processor computer
#define	IMAGE_FILE_BYTES_REVERSED_HI 0x8000 	//The bytes of the word are reversed(obsolete)

//Image Data
#define	IMAGE_NT_OPTIONAL_HDR32_MAGIC 	0x10b 	//32 bit executable image.
#define	IMAGE_NT_OPTIONAL_HDR64_MAGIC 	0x20b 	//64 bit executable image
#define	IMAGE_ROM_OPTIONAL_HDR_MAGIC 	0x107 	//ROM image

//Image Subsystem
#define	IMAGE_SUBSYSTEM_UNKNOWN 	0 	//Unknown subsystem
#define	IMAGE_SUBSYSTEM_NATIVE 	1 	//No subsystem required (device drivers and native system processes)
#define	IMAGE_SUBSYSTEM_WINDOWS_GUI 	2 	//Windows graphical user interface (GUI) subsystem
#define	IMAGE_SUBSYSTEM_WINDOWS_CUI 	3 	//Windows character-mode user interface (CUI) subsystem
#define	IMAGE_SUBSYSTEM_OS2_CUI 	5 	//OS/2 CUI subsystem
#define	IMAGE_SUBSYSTEM_POSIX_CUI 	7 	//POSIX CUI subsystem
#define	IMAGE_SUBSYSTEM_WINDOWS_CE_GUI 	9 	//Windows CE system
#define	IMAGE_SUBSYSTEM_EFI_APPLICATION 	10 	//Extensible Firmware Interface (EFI) application
#define	IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 	11 	//EFI driver with boot services
#define	IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 	12 	//EFI driver with run-time services
#define	IMAGE_SUBSYSTEM_EFI_ROM 	13 	//EFI ROM image
#define	IMAGE_SUBSYSTEM_XBOX 	14 	//Xbox system
#define	IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION 	16 	//Boot application

//DLL Characteristics

#define	IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE 	0x0040 	//The DLL can be relocated at load time
#define	IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY 	0x0080 	//Code integrity checks are forced
#define	IMAGE_DLLCHARACTERISTICS_NX_COMPAT 	0x0100 	//The image is compatible with data execution prevention (DEP)
#define	IMAGE_DLLCHARACTERISTICS_NO_ISOLATION 	0x0200 	//The image is isolation aware, but should not be isolated
#define	IMAGE_DLLCHARACTERISTICS_NO_SEH 	0x0400 	//The image does not use structured exception handling (SEH). No handlers can be called in this image
#define	IMAGE_DLLCHARACTERISTICS_NO_BIND 	0x0800 	//Do not bind the image
#define	IMAGE_DLLCHARACTERISTICS_APPCONTAINER 	0x1000 	//The image must be executed within an App container
#define	IMAGE_DLLCHARACTERISTICS_WDM_DRIVER 	0x2000 	//A WDM driver
#define	IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE 	0x8000 	//The image is terminal server aware

//Image Directory Data (Type, 32-Bit offset , 64-bit offset)

#define	IMAGE_DIRECTORY_ENTRY_EXPORT 	0 	//Export Directory 	96 	112
#define	IMAGE_DIRECTORY_ENTRY_IMPORT 	1 	//Import Directory 	104 	120
#define	IMAGE_DIRECTORY_ENTRY_RESOURCE 	2 	//Resource Directory 	112 	128
#define	IMAGE_DIRECTORY_ENTRY_EXCEPTION 	3 	//Exception Directory 	120 	136
#define	IMAGE_DIRECTORY_ENTRY_SECURITY 	4 	//Security Directory 	128 	144
#define	IMAGE_DIRECTORY_ENTRY_BASERELOC 	5 	//Base Relocation Table 	136 	152
#define	IMAGE_DIRECTORY_ENTRY_DEBUG 	6 	//Debug Directory 	144 	160
#define	IMAGE_DIRECTORY_ENTRY_ARCHITECTURE 	7 	//Architecture specific data 	152 	168
#define	IMAGE_DIRECTORY_ENTRY_GLOBALPTR 	8 	//Global pointer register relative virtual address 	160 	176
#define	IMAGE_DIRECTORY_ENTRY_TLS 	9 	//Thread Local Storage directory 	168 	184
#define	IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG 	10 	//Load Configuration directory 	176 	192
#define	IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT 	11 	//Bound Import directory 	184 	200
#define	IMAGE_DIRECTORY_ENTRY_IAT 	12 	//Import Address Table 	192 	208
#define	IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT 	13 	//Delay Import table 	200 	216
#define	IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 	14 	//COM descriptor table 	208 	224

//Image characteristics
//No Constant Name 	0x00000000 	Reserved
//No Constant Name 	0x00000001 	Reserved
//No Constant Name 	0x00000002 	Reserved
//No Constant Name 	0x00000004 	Reserved
#define	IMAGE_SCN_TYPE_NO_PAD 	0x00000008 	//The section should not be padded to the next boundary. This flag is obsolete and is replaced by IMAGE_SCN_ALIGN_1BYTES
//No Constant Name 	0x00000010 	Reserved
#define	IMAGE_SCN_CNT_CODE 	0x00000020 	//The section contains executable code
#define	IMAGE_SCN_CNT_INITIALIZED_DATA 	0x00000040 	//The section contains initialized data
#define	IMAGE_SCN_CNT_UNINITIALIZED_DATA 	0x00000080 	//The section contains uninitialized data
#define	IMAGE_SCN_LNK_OTHER 	0x00000100 	//Reserved
#define	IMAGE_SCN_LNK_INFO 	0x00000200 	//The section contains comments or other information. This is valid only for object files
//No Constant Name 	0x00000400 	//Reserved
#define	IMAGE_SCN_LNK_REMOVE 	0x00000800 	//The section will not become part of the image. This is valid only for object files
#define	IMAGE_SCN_LNK_COMDAT 	0x00001000 	//The section contains COMDAT data. This is valid only for object files
//No Constant Name 	0x00002000 	//Reserved
#define	IMAGE_SCN_NO_DEFER_SPEC_EXC 	0x00004000 	//Reset speculative exceptions handling bits in the TLB entries for this section
#define	IMAGE_SCN_GPREL 	0x00008000 	//The section contains data referenced through the global pointer
//No Constant Name 	0x00010000 	Reserved
#define	IMAGE_SCN_MEM_PURGEABLE 	0x00020000 	//Reserved
#define	IMAGE_SCN_MEM_LOCKED 	0x00040000 	//Reserved
#define	IMAGE_SCN_MEM_PRELOAD 	0x00080000 	//Reserved
#define	IMAGE_SCN_ALIGN_1BYTES 	0x00100000 	//Align data on a 1-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_2BYTES 	0x00200000 	//Align data on a 2-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_4BYTES 	0x00300000 	//Align data on a 4-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_8BYTES 	0x00400000 //Align data on a 8-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_16BYTES 	0x00500000 	//Align data on a 16-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_32BYTES 	0x00600000 	//Align data on a 32-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_64BYTES 	0x00700000 	//Align data on a 64-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_128BYTES 	0x00800000 //Align data on a 128-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_256BYTES 	0x00900000 //Align data on a 256-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_512BYTES 	0x00A00000 	//Align data on a 512-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_1024BYTES 	0x00B00000 	//Align data on a 1024-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_2048BYTES 	0x00C00000 	//Align data on a 2048-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_4096BYTES 	0x00D00000 	//Align data on a 4096-byte boundary. This is valid only for object files
#define	IMAGE_SCN_ALIGN_8192BYTES 	0x00E00000 	//Align data on a 8192-byte boundary. This is valid only for object files
#define	IMAGE_SCN_LNK_NRELOC_OVFL 	0x01000000 	//The section contains extended relocations. The count of relocations for the section exceeds the 16 bits that is reserved for it in the section header. If the NumberOfRelocations field in the section header is 0xffff, the actual relocation count is stored in the VirtualAddress field of the first relocation. It is an error if IMAGE_SCN_LNK_NRELOC_OVFL is set and there are fewer than 0xffff relocations in the section
#define	IMAGE_SCN_MEM_DISCARDABLE 	0x02000000 	//The section can be discarded as needed
#define	IMAGE_SCN_MEM_NOT_CACHED 	0x04000000 	//The section cannot be cached
#define	IMAGE_SCN_MEM_NOT_PAGED 	0x08000000 	//The section cannot be paged
#define	IMAGE_SCN_MEM_SHARED 	0x10000000 	//The section can be shared in memory
#define	IMAGE_SCN_MEM_EXECUTE 	0x20000000 	//The section can be executed as code
#define	MAGE_SCN_MEM_READ 	0x40000000 	//The section can be read
#define	IMAGE_SCN_MEM_WRITE 	0x80000000 	//The section can be written to

struct data_directory
{
   int32_t VirtualAddress;
   int32_t Size;
};

typedef struct data_directory data_directory_t;

struct PEOptHeader64
{
/* 64 bit version of the PE Optional Header also known as IMAGE_OPTIONAL_HEADER64

*/
   int16_t signature; //decimal number 267 for 32 bit, 523 for 64 bit, and 263 for a ROM image.
   int8_t MajorLinkerVersion;
   int8_t MinorLinkerVersion;
   int32_t SizeOfCode;
   int32_t SizeOfInitializedData;
   int32_t SizeOfUninitializedData;
   int32_t AddressOfEntryPoint;  //The RVA of the code entry point
   int32_t BaseOfCode;
   /*The next 21 fields are an extension to the COFF optional header format*/
   int64_t ImageBase;
   int32_t SectionAlignment;
   int32_t FileAlignment;
   int16_t MajorOSVersion;
   int16_t MinorOSVersion;
   int16_t MajorImageVersion;
   int16_t MinorImageVersion;
   int16_t MajorSubsystemVersion;
   int16_t MinorSubsystemVersion;
   int32_t Win32VersionValue;
   int32_t SizeOfImage;
   int32_t SizeOfHeaders;
   int32_t Checksum;
   int16_t Subsystem;
   int16_t DLLCharacteristics;
   int64_t SizeOfStackReserve;
   int64_t SizeOfStackCommit;
   int64_t SizeOfHeapReserve;
   int64_t SizeOfHeapCommit;
   int32_t LoaderFlags;
   int32_t NumberOfRvaAndSizes;
   data_directory_t DataDirectory[NumberOfRvaAndSizes];     //Can have any number of elements, matching the number in NumberOfRvaAndSizes.
}; //However, it is always 16 in PE files.;

struct PEOptHeader32
{
/* 32 bit version of the PE Optional Header also known as IMAGE_OPTIONAL_HEADER

*/
   int16_t signature; //decimal number 267 for 32 bit, 523 for 64 bit, and 263 for a ROM image.
   int8_t MajorLinkerVersion;
   int8_t MinorLinkerVersion;
   int32_t SizeOfCode;
   int32_t SizeOfInitializedData;
   int32_t SizeOfUninitializedData;
   int32_t AddressOfEntryPoint;  //The RVA of the code entry point
   int32_t BaseOfCode;
   int32_t BaseOfData;
   /*The next 21 fields are an extension to the COFF optional header format*/
   int32_t ImageBase;
   int32_t SectionAlignment;
   int32_t FileAlignment;
   int16_t MajorOSVersion;
   int16_t MinorOSVersion;
   int16_t MajorImageVersion;
   int16_t MinorImageVersion;
   int16_t MajorSubsystemVersion;
   int16_t MinorSubsystemVersion;
   int32_t Win32VersionValue;
   int32_t SizeOfImage;
   int32_t SizeOfHeaders;
   int32_t Checksum;
   int16_t Subsystem;
   int16_t DLLint8_tacteristics;
   int32_t SizeOfStackReserve;
   int32_t SizeOfStackCommit;
   int32_t SizeOfHeapReserve;
   int32_t SizeOfHeapCommit;
   int32_t LoaderFlags;
   int32_t NumberOfRvaAndSizes;
   data_directory_t DataDirectory[NumberOfRvaAndSizes];     //Can have any number of elements, matching the number in NumberOfRvaAndSizes.
};                                        //However, it is always 16 in PE files.

struct IMAGE_SECTION_HEADER
{

 char  Name[8];
 union {
   int32_t PhysicalAddress;
   int32_t VirtualSize;
 } Misc;
 int32_t  VirtualAddress;
 int32_t  SizeOfRawData;
 int32_t  PointerToRawData;
 int32_t  PointerToRelocations;
 int32_t  PointerToLinenumbers;
 int16_t NumberOfRelocations;
 int16_t NumberOfLinenumbers;
 int32_t  Characteristics;
};

typedef struct IMAGE_SECTION_HEADER image_section_header_t;

struct IMAGE_IMPORT_DESCRIPTOR {
	int32_t *OriginalFirstThunk;
	int32_t TimeDateStamp;
	int32_t ForwarderChain;
	int32_t Name;
	int32_t *FirstThunk;
};

typedef struct IMAGE_IMPORT_DESCRIPTOR image_import_descriptor_t;

struct IMAGE_IMPORT_BY_NAME {
	int16_t Hint;
	char Name[1];
};

typedef struct IMAGE_IMPORT_BY_NAME image_import_by_name_t;

struct IMAGE_RESOURCE_DIRECTORY
{
	int32_t Characteristics;
	int32_t TimeDateStamp;
	int16_t MajorVersion;
	int16_t MinorVersion;
	int16_t NumberOfNamedEntries;
	int16_t NumberOfIdEntries;
}

typedef struct IMAGE_RESOURCE_DIRECTORY image_resource_directory_t;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY
{
	int32_t NameId;
	int32_t *Data;
}

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY image_resource_directory_t;

struct IMAGE_RESOURCE_DATA_ENTRY
{
  int32_t *Data;
  int32_t Size;
  int32_t CodePage;
  int32_t Reserved;
};

typedef struct IMAGE_RESOURCE_DATA_ENTRY image_resource_data_entry_t;

#endif
