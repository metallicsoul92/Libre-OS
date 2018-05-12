#ifndef LIBRE_OS_ATA_H
#define LIBRE_OS_ATA_H

/*Definitions */
#define ATA_BLOCKSIZE 512

#define ATA_IRQ0	32+14
#define ATA_IRQ1	32+15
#define ATA_IRQ2	32+11
#define ATA_IRQ3	32+9

#define ATA_BASE0	0x1F0
#define ATA_BASE1	0x170
#define ATA_BASE2	0x1E8
#define ATA_BASE3	0x168

#define ATA_TIMEOUT     3

#define ATA_DATA	0   /* data register */
#define ATA_ERROR	1   /* error register */
#define ATA_COUNT	2   /* sectors to transfer */
#define ATA_SECTOR	3   /* sector number */
#define ATA_CYL_LO	4   /* low byte of cylinder number */
#define ATA_CYL_HI	5   /* high byte of cylinder number */
#define ATA_FDH		6   /* flags, drive and head */
#define ATA_STATUS	7
#define ATA_COMMAND	7
#define ATA_CONTROL	0x206

#define ATA_FLAGS_ECC	0x80	/* enable error correction */
#define ATA_FLAGS_LBA	0x40	/* enable linear addressing */
#define ATA_FLAGS_SEC	0x20	/* enable 512-byte sectors */
#define ATA_FLAGS_SLV	0x10	/* address the slave drive */

#define ATA_STATUS_BSY	0x80    /* controller busy */
#define ATA_STATUS_RDY	0x40    /* drive ready */
#define ATA_STATUS_WF	0x20    /* write fault */
#define ATA_STATUS_SC	0x10    /* seek complete (obsolete) */
#define ATA_STATUS_DRQ	0x08    /* data transfer request */
#define ATA_STATUS_CRD	0x04    /* corrected data */
#define ATA_STATUS_IDX	0x02    /* index pulse */
#define ATA_STATUS_ERR	0x01    /* error */

#define ATA_COMMAND_IDLE		0x00
#define ATA_COMMAND_READ		0x20    /* read data */
#define ATA_COMMAND_WRITE		0x30    /* write data */
#define ATA_COMMAND_IDENTIFY		0xec

#define ATAPI_COMMAND_IDENTIFY 0xa1
#define ATAPI_COMMAND_PACKET   0xa0

#define ATAPI_FEATURE	1
#define ATAPI_IRR 2
#define ATAPI_SAMTAG 3
#define ATAPI_COUNT_LO 4
#define ATAPI_COUNT_HI 5
#define ATAPI_DRIVE 6
#define ATAPI_BLOCKSIZE 2048

#define SCSI_READ10            0x28
#define SCSI_SENSE             0x03

#define ATA_CONTROL_RESET	0x04
#define ATA_CONTROL_DISABLEINT	0x02

/* Structures */
typedef struct ata_drive_info ata_drive_info_t;



/* Functions */
void ata_init();

void ata_reset(int);
int ata_probe(int, int *, int *, char *);

int ata_read(int, void *, int, int);
int ata_write(int, void *, int, int);
int ata_read_bytes(int, void *, int, int);
int ata_write_bytes(int, void *, int nblocks, int offset);
int atapi_read(int, void *, int, int);


#endif
