#ifndef DRIVER_EXEC_ELF_H_
#define DRIVER_EXEC_ELF_H_

#include <stdint.h>


//Elf32 Data Types
typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;
//NOTE: unsigned char is also defined but already in C Library

//Elf64 Data Types
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef int64_t Elf64_Sxword;
typedef uint364_t Elf64_Xword;
//NOTE: unsigned char is also defined but already in C Library


// Define ELFMAG0-3
#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'


//Define Class type
#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2


//Define Data type
#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

//Define e_types

#define ET_NONE 0 //No file type
#define ET_REL 1 //Relocatable file
#define ET_EXEC 2 //Executable file
#define ET_DYN 3 //Shared object file
#define ET_CORE 4 //Core file
#define ET_LOOS 0xfe00 //Operating system-specific
#define ET_HIOS 0xfeff //Operating system-specific
#define ET_LOPROC 0xff00 //Processor-specific
#define ET_HIPROC 0xffff //Processor-specific

//define machine
#define EM_NONE 0 //No machine
#define EM_M32 	1 //AT&T WE 32100
#define EM_SPARC 2 //SPARC
#define EM_386 	3 //Intel 80386
#define EM_68K 	4 //Motorola 68000
#define EM_88K 	5 //Motorola 88000
#define EM_IAMCU 6 //Intel MCU
#define EM_860 	7 //Intel 80860
#define EM_MIPS 8 //MIPS I Architecture
#define EM_S370 9 //IBM System/370 Processor
#define EM_MIPS_RS3_LE 	10 //MIPS RS3000 Little-endian
//11-14 Reserved for future use
#define EM_PARISC 15 //Hewlett-Packard PA-RISC
//reserved 16 //Reserved for future use
#define EM_VPP500 17 //Fujitsu VPP500
#define EM_SPARC32PLUS 	18 //Enhanced instruction set SPARC
#define EM_960 	19 //Intel 80960
#define EM_PPC 	20 //PowerPC
#define EM_PPC64 21 //64-bit PowerPC
#define EM_S390 22 //IBM System/390 Processor
#define EM_SPU 	23 //IBM SPU/SPC
//24-35 	Reserved for future use
#define EM_V800 36 //NEC V800
#define EM_FR20 37 //Fujitsu FR20
#define EM_RH32 38 //TRW RH-32
#define EM_RCE 	39 //Motorola RCE
#define EM_ARM 	40 //ARM 32-bit architecture (AARCH32)
#define EM_ALPHA 41 //Digital Alpha
#define EM_SH 	42 //Hitachi SH
#define EM_SPARCV9 43 //SPARC Version 9
#define EM_TRICORE 44 //Siemens TriCore embedded processor
#define EM_ARC 	45 //Argonaut RISC Core, Argonaut Technologies Inc.
#define EM_H8_300 46 //Hitachi H8/300
#define EM_H8_300H 47 //Hitachi H8/300H
#define EM_H8S 	48 //Hitachi H8S
#define EM_H8_500 49 //Hitachi H8/500
#define EM_IA_64 50 //Intel IA-64 processor architecture
#define EM_MIPS_X 51 //Stanford MIPS-X
#define EM_COLDFIRE 52 //Motorola ColdFire
#define EM_68HC12 53 //Motorola M68HC12
#define EM_MMA 	54 //Fujitsu MMA Multimedia Accelerator
#define EM_PCP 	55 //Siemens PCP
#define EM_NCPU 56 //Sony nCPU embedded RISC processor
#define EM_NDR1 57 //Denso NDR1 microprocessor
#define EM_STARCORE 58 //Motorola Star*Core processor
#define EM_ME16 59 //Toyota ME16 processor
#define EM_ST100 60 //STMicroelectronics ST100 processor
#define EM_TINYJ 61 //Advanced Logic Corp. TinyJ embedded processor family
#define EM_X86_64 62 //AMD x86-64 architecture
#define EM_PDSP 63 //Sony DSP Processor
#define EM_PDP10 64 //Digital Equipment Corp. PDP-10
#define EM_PDP11 65 //Digital Equipment Corp. PDP-11
#define EM_FX66 66 //Siemens FX66 microcontroller
#define EM_ST9PLUS 67 //STMicroelectronics ST9+ 8/16 bit microcontroller
#define EM_ST7 	68 //STMicroelectronics ST7 8-bit microcontroller
#define EM_68HC16 69 //Motorola MC68HC16 Microcontroller
#define EM_68HC11 70 //Motorola MC68HC11 Microcontroller
#define EM_68HC08 71 //Motorola MC68HC08 Microcontroller
#define EM_68HC05 72 //Motorola MC68HC05 Microcontroller
#define EM_SVX 	73 //Silicon Graphics SVx
#define EM_ST19 74 //STMicroelectronics ST19 8-bit microcontroller
#define EM_VAX 	75 //Digital VAX
#define EM_CRIS 76 //Axis Communications 32-bit embedded processor
#define EM_JAVELIN 77 //Infineon Technologies 32-bit embedded processor
#define EM_FIREPATH 78 //Element 14 64-bit DSP Processor
#define EM_ZSP 	79 //LSI Logic 16-bit DSP Processor
#define EM_MMIX 80 //Donald Knuth's educational 64-bit processor
#define EM_HUANY 81 //Harvard University machine-independent object files
#define EM_PRISM 82 //SiTera Prism
#define EM_AVR 	83 //Atmel AVR 8-bit microcontroller
#define EM_FR30 84 //Fujitsu FR30
#define EM_D10V 85 //Mitsubishi D10V
#define EM_D30V 86 //Mitsubishi D30V
#define EM_V850 87 //NEC v850
#define EM_M32R 88 //Mitsubishi M32R
#define EM_MN10300 89 //Matsushita MN10300
#define EM_MN10200 90 //Matsushita MN10200
#define EM_PJ 	91 //picoJava
#define EM_OPENRISC 92 //OpenRISC 32-bit embedded processor
#define EM_ARC_COMPACT	93 //ARC International ARCompact processor (old spelling/synonym: EM_ARC_A5)
#define EM_XTENSA 94 //Tensilica Xtensa Architecture
#define EM_VIDEOCORE 95 //Alphamosaic VideoCore processor
#define EM_TMM_GPP 96 //Thompson Multimedia General Purpose Processor
#define EM_NS32K 97 //National Semiconductor 32000 series
#define EM_TPC 98 //Tenor Network TPC processor
#define EM_SNP1K 99 //Trebia SNP 1000 processor
#define EM_ST200 100 //STMicroelectronics (www.st.com) ST200 microcontroller
#define EM_IP2K 101 //Ubicom IP2xxx microcontroller family
#define EM_MAX 102 //MAX Processor
#define EM_CR 103 //National Semiconductor CompactRISC microprocessor
#define EM_F2MC16 104 //Fujitsu F2MC16
#define EM_MSP430 105 //Texas Instruments embedded microcontroller msp430
#define EM_BLACKFIN 106 //Analog Devices Blackfin (DSP) processor
#define EM_SE_C33 107 //S1C33 Family of Seiko Epson processors
#define EM_SEP 	108 //Sharp embedded microprocessor
#define EM_ARCA 109 //Arca RISC Microprocessor
#define EM_UNICORE 110 //Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
#define EM_EXCESS 111 //eXcess: 16/32/64-bit configurable embedded CPU
#define EM_DXP 	112 //Icera Semiconductor Inc. Deep Execution Processor
#define EM_ALTERA_NIOS2 113 //Altera Nios II soft-core processor
#define EM_CRX 	114 //National Semiconductor CompactRISC CRX microprocessor
#define EM_XGATE 115 //Motorola XGATE embedded processor
#define EM_C166 116 //Infineon C16x/XC16x processor
#define EM_M16C 117 //Renesas M16C series microprocessors
#define EM_DSPIC30F 118 //Microchip Technology dsPIC30F Digital Signal Controller
#define EM_CE 	119 //Freescale Communication Engine RISC core
#define EM_M32C 120 //Renesas M32C series microprocessors
//121-130 	Reserved for future use
#define EM_TSK3000 131 //Altium TSK3000 core
#define EM_RS08 132 //Freescale RS08 embedded processor
#define EM_SHARC 133 //Analog Devices SHARC family of 32-bit DSP processors
#define EM_ECOG2 134 //Cyan Technology eCOG2 microprocessor
#define EM_SCORE7 135 //Sunplus S+core7 RISC processor
#define EM_DSP24 136 //New Japan Radio (NJR) 24-bit DSP Processor
#define EM_VIDEOCORE3 137 //Broadcom VideoCore III processor
#define EM_LATTICEMICO32 138 //RISC processor for Lattice FPGA architecture
#define EM_SE_C17 139 //Seiko Epson C17 family
#define EM_TI_C6000 140 //The Texas Instruments TMS320C6000 DSP family
#define EM_TI_C2000 141 //The Texas Instruments TMS320C2000 DSP family
#define EM_TI_C5500 142 //The Texas Instruments TMS320C55x DSP family
#define EM_TI_ARP32 143 //Texas Instruments Application Specific RISC Processor, 32bit fetch
#define EM_TI_PRU 144 //Texas Instruments Programmable Realtime Unit
//145-159 	Reserved for future use
#define EM_MMDSP_PLUS 160 //STMicroelectronics 64bit VLIW Data Signal Processor
#define EM_CYPRESS_M8C 	161 //Cypress M8C microprocessor
#define EM_R32C 162 //Renesas R32C series microprocessors
#define EM_TRIMEDIA 163 //NXP Semiconductors TriMedia architecture family
#define EM_QDSP6 164 //QUALCOMM DSP6 Processor
#define EM_8051 165 //Intel 8051 and variants
#define EM_STXP7X 166 //STMicroelectronics STxP7x family of configurable and extensible RISC processors
#define EM_NDS32 167 //Andes Technology compact code size embedded RISC processor family
#define EM_ECOG1 168 //Cyan Technology eCOG1X family
#define EM_ECOG1X 168 //Cyan Technology eCOG1X family
#define EM_MAXQ30 169 //Dallas Semiconductor MAXQ30 Core Micro-controllers
#define EM_XIMO16 170 //New Japan Radio (NJR) 16-bit DSP Processor
#define EM_MANIK 171 //M2000 Reconfigurable RISC Microprocessor
#define EM_CRAYNV2 172 //Cray Inc. NV2 vector architecture
#define EM_RX 	173 //Renesas RX family
#define EM_METAG 174 //Imagination Technologies META processor architecture
#define EM_MCST_ELBRUS 	175 //MCST Elbrus general purpose hardware architecture
#define EM_ECOG16 176 //Cyan Technology eCOG16 family
#define EM_CR16 177 //National Semiconductor CompactRISC CR16 16-bit microprocessor
#define EM_ETPU 178 //Freescale Extended Time Processing Unit
#define EM_SLE9X 179 //Infineon Technologies SLE9X core
#define EM_L10M 180 //Intel L10M
#define EM_K10M 181 //Intel K10M
//182 Reserved for future Intel use
#define EM_AARCH64 183 //ARM 64-bit architecture (AARCH64)
//184 Reserved for future ARM use
#define EM_AVR32 185 //Atmel Corporation 32-bit microprocessor family
#define EM_STM8 186 //STMicroeletronics STM8 8-bit microcontroller
#define EM_TILE64 187 //Tilera TILE64 multicore architecture family
#define EM_TILEPRO 188 //Tilera TILEPro multicore architecture family
#define EM_MICROBLAZE 189 //Xilinx MicroBlaze 32-bit RISC soft processor core
#define EM_CUDA 190 //NVIDIA CUDA architecture
#define EM_TILEGX 191 //Tilera TILE-Gx multicore architecture family
#define EM_CLOUDSHIELD 192 //CloudShield architecture family
#define EM_COREA_1ST 193 //KIPO-KAIST Core-A 1st generation processor family
#define EM_COREA_2ND 194 //KIPO-KAIST Core-A 2nd generation processor family
#define EM_ARC_COMPACT2 195 //Synopsys ARCompact V2
#define EM_OPEN8 196 //Open8 8-bit RISC soft processor core
#define EM_RL78 197 //Renesas RL78 family
#define EM_VIDEOCORE5 198 //Broadcom VideoCore V processor
#define EM_78KOR 199 //Renesas 78KOR family
#define EM_56800EX 200 //Freescale 56800EX Digital Signal Controller (DSC)
#define EM_BA1 	201 //Beyond BA1 CPU architecture
#define EM_BA2 	202 //Beyond BA2 CPU architecture
#define EM_XCORE 203 //XMOS xCORE processor family
#define EM_MCHP_PIC 204 //Microchip 8-bit PIC(r) family
#define EM_INTEL205 205 //Reserved by Intel
#define EM_INTEL206 206 //Reserved by Intel
#define EM_INTEL207 207 //Reserved by Intel
#define EM_INTEL208 208 //Reserved by Intel
#define EM_INTEL209 209 //Reserved by Intel
#define EM_KM32 210 //KM211 KM32 32-bit processor
#define EM_KMX32 211 //KM211 KMX32 32-bit processor
#define EM_KMX16 212 //KM211 KMX16 16-bit processor
#define EM_KMX8 213 //KM211 KMX8 8-bit processor
#define EM_KVARC 214 //KM211 KVARC processor
#define EM_CDP 	215 //Paneve CDP architecture family
#define EM_COGE 216 //Cognitive Smart Memory Processor
#define EM_COOL 217 //Bluechip Systems CoolEngine
#define EM_NORC 218 //Nanoradio Optimized RISC
#define EM_CSR_KALIMBA 	219 //CSR Kalimba architecture family
#define EM_Z80 	220 //Zilog Z80
#define EM_VISIUM 221 //Controls and Data Services VISIUMcore processor
#define EM_FT32 222 //FTDI Chip FT32 high performance 32-bit RISC architecture
#define EM_MOXIE 223 //Moxie processor family
#define EM_AMDGPU 224 //AMD GPU architecture
//225 - 242
#define EM_RISCV 243 //RISC-V

#define EV_NONE 0 //Invalid version
#define EV_CURRENT 1 //Current version

#define ELFOSABI_NONE 0 //No extensions or unspecified
#define ELFOSABI_HPUX 1 //Hewlett-Packard HP-UX
#define ELFOSABI_NETBSD 2 //NetBSD
#define ELFOSABI_GNU 3 //GNU
#define ELFOSABI_LINUX 3 //Linux
#define ELFOSABI_SOLARIS 6 //Sun Solaris
#define ELFOSABI_AIX 7 //AIX
#define ELFOSABI_IRIX 8 //IRIX
#define ELFOSABI_FREEBSD 9 //FreeBSD
#define ELFOSABI_TRU64 10 //Compaq TRU64 UNIX
#define ELFOSABI_MODESTO 11 //Novell Modesto
#define ELFOSABI_OPENBSD 12 //Open BSD
#define ELFOSABI_OPENVMS 13 //Open VMS
#define ELFOSABI_NSK 14 //Hewlett-Packard Non-Stop Kernel
#define ELFOSABI_AROS 15 //Amiga Research OS
#define ELFOSABI_FENIXOS 16 //The FenixOS highly scalable multi-core OS
#define ELFOSABI_CLOUDABI 17 //Nuxi CloudABI
#define ELFOSABI_OPENVOS 18 //Stratus Technologies OpenVOS
//64-255 Architecture-specific value range





//define e_flags
#define EF_SPARC_EXT_MASK 0xFFFF00
#define EF_SPARC_32PLUS 0x000100
#define EF_SPARC_SUN_

//define e_ident indexes
#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_OSABI 7
#define EI_ABIVERSION 8
#define EI_PAD 9
#define EI_NIDENT 16

//Special Section indexes
#define SHN_UNDEF 	0
#define SHN_LORESERVE 	0xff00
#define SHN_LOPROC 	0xff00
#define SHN_HIPROC 	0xff1f
#define SHN_LOOS 	0xff20
#define SHN_HIOS 	0xff3f
#define SHN_ABS 	0xfff1
#define SHN_COMMON 	0xfff2
#define SHN_XINDEX 	0xffff
#define SHN_HIRESERVE 	0xffff

//Section Types
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_LOOS 0x60000000
#define SHT_HIOS 0x6fffffff
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

//Section Attribute flags
#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MERGE 0x10
#define SHF_STRINGS 0x20
#define SHF_INFO_LINK 0x40
#define SHF_LINK_ORDER 0x80
#define SHF_OS_NONCONFORMING 0x100
#define SHF_GROUP 0x200
#define SHF_TLS 0x400
#define SHF_COMPRESSED 0x800
#define SHF_MASKOS 0x0ff00000
#define SHF_MASKPROC 0xf0000000

//Compression Types
#define ELFCOMPRESS_ZLIB 1
#define ELFCOMPRESS_LOOS 0x60000000
#define ELFCOMPRESS_HIOS 0x6fffffff
#define ELFCOMPRESS_LOPROC 0x70000000
#define ELFCOMPRESS_HIPROC 0x7fffffff

//Section Group Flags
#define GRP_COMDAT 0x1
#define GRP_MASKOS 0x0ff00000
#define GRP_MASKPROC 0xf0000000

#define STN_UNDEF 0

//Symbol Binding
#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_LOOS 10
#define STB_HIOS 12
#define STB_LOPROC 13
#define STB_HIPROC 15

//Symbol Types
#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_COMMON 5
#define STT_TLS 6
#define STT_LOOS 10
#define STT_HIOS 12
#define STT_LOPROC 13
#define STT_HIPROC 15

//Symbol Visibility
#define STV_DEFAULT 0
#define STV_INTERNAL 1
#define STV_HIDDEN 2
#define STV_PROTECTED 3

//Segment Types
#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_TLS 	7
#define PT_LOOS 0x60000000
#define PT_HIOS 0x6fffffff
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7fffffff


#define ELF32_ST_BIND(i)   ((i)>>4)
#define ELF32_ST_TYPE(i)   ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
#define ELF32_ST_VISIBILITY(o) ((o)&0x3)


#define ELF64_ST_BIND(i)   ((i)>>4)
#define ELF64_ST_TYPE(i)   ((i)&0xf)
#define ELF64_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
#define ELF64_ST_VISIBILITY(o) ((o)&0x3)

#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

#define ELF64_R_SYM(i)    ((i)>>32)
#define ELF64_R_TYPE(i)   ((i)&0xffffffffL)
#define ELF64_R_INFO(s,t) (((s)<<32)+((t)&0xffffffffL))


//Elf32
typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half    e_type;
  Elf32_Half    e_machine;
  Elf32_Word    e_version;
  Elf32_Addr    e_entry;
  Elf32_Off     e_phoff;
  Elf32_Off     e_shoff;
  Elf32_Word    e_flags;
  Elf32_Half    e_ehsize;
  Elf32_Half    e_phentsize;
  Elf32_Half    e_phnum;
  Elf32_Half    e_shentsize;
  Elf32_Half    e_shnum;
  Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

//Elf64
typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half    e_type;
  Elf64_Half    e_machine;
  Elf64_Word    e_version;
  Elf64_Addr    e_entry;
  Elf64_Off     e_phoff;
  Elf64_Off     e_shoff;
  Elf64_Word    e_flags;
  Elf64_Half    e_ehsize;
  Elf64_Half    e_phentsize;
  Elf64_Half    e_phnum;
  Elf64_Half    e_shentsize;
  Elf64_Half    e_shnum;
  Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

//Section Header 32
typedef struct {
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
} Elf32_Shdr;

//Section Header 64
typedef struct {
	Elf64_Word	sh_name;
	Elf64_Word	sh_type;
	Elf64_Xword	sh_flags;
	Elf64_Addr	sh_addr;
	Elf64_Off	sh_offset;
	Elf64_Xword	sh_size;
	Elf64_Word	sh_link;
	Elf64_Word	sh_info;
	Elf64_Xword	sh_addralign;
	Elf64_Xword	sh_entsize;
} Elf64_Shdr;


//Compression Header 32
typedef struct {
	Elf32_Word	ch_type;
	Elf32_Word	ch_size;
	Elf32_Word	ch_addralign;
} Elf32_Chdr;

//Compression header 64
typedef struct {
	Elf64_Word	ch_type;
	Elf64_Word	ch_reserved;
	Elf64_Xword	ch_size;
	Elf64_Xword	ch_addralign;
} Elf64_Chdr;

//symbol table 32
typedef struct {
	Elf32_Word	st_name;
	Elf32_Addr	st_value;
	Elf32_Word	st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf32_Half	st_shndx;
} Elf32_Sym;

//Symbol Table 64
typedef struct {
	Elf64_Word	st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf64_Half	st_shndx;
	Elf64_Addr	st_value;
	Elf64_Xword	st_size;
} Elf64_Sym;

//Relocation Entry 32bit
typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;
} Elf32_Rel;


typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;
	Elf32_Sword	r_addend;
} Elf32_Rela;

//Relocation Entry 64bit
typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Xword	r_info;
} Elf64_Rel;

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Xword	r_info;
	Elf64_Sxword	r_addend;
} Elf64_Rela;

//32 Bit Program Header
typedef struct {
	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;
} Elf32_Phdr;
//64 Bit Program Header
typedef struct {
	Elf64_Word	p_type;
	Elf64_Word	p_flags;
	Elf64_Off	p_offset;
	Elf64_Addr	p_vaddr;
	Elf64_Addr	p_paddr;
	Elf64_Xword	p_filesz;
	Elf64_Xword	p_memsz;
	Elf64_Xword	p_align;
} Elf64_Phdr;

int isELF(uint8_t * elf);
unsigned long loadELF(void * elf);

#endif
