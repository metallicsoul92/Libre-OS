#include "../include/drivers/ata.h"
#include "../include/tty.h"
#include "../include/inlineAssembly.h"
#include "../libc/include/string.h"
#include "../libc/include/stdint.h"


struct ata_drive_info
{
	uint8_t  attached;
	const char *name;
	int block_size;
	uint64_t size;
};

static const int ata_base[4] = {
	ATA_BASE0,
	ATA_BASE0,
	ATA_BASE1,
	ATA_BASE1
};

static struct ata_drive_info drives[4];


void ata_reset(int id) {
	outb(ata_base[id] + ATA_CONTROL, ATA_CONTROL_RESET);
	/*TODO: Implement */ sleep(5);
	outb(ata_base[id] + ATA_CONTROL, 0);
	/*TODO: Implement*/ sleep(5);
}

static int ata_wait(int id, int mask, int state) {
	int t;
	int time=0;
	while(1) {
		t = inb(ata_base[id] + ATA_STATUS);
		if((t&mask) == state) {
			return 1;
		}
		if(t&ATA_STATUS_ERR) {
			printk("ATA error on drive %u", id);
			ata_reset(id);
			return 0;
		}
		if(time>=ATA_TIMEOUT*100)
		{
			printk("ATA timeout on drive %u", id);
			ata_reset(id);
			return 0;
		}
		sleep(1);
		time++;
	}
}

static void ata_pio_read(int id, void *buffer, int size) {
	uint16_t *wbuffer = (uint16_t*)buffer;
	while(size > 0) {
		*wbuffer = inw(ata_base[id] + ATA_DATA);
		wbuffer++;
		size -= 2;
	}
}

static void ata_pio_write(int id, const void *buffer, int size) {
	uint16_t *wbuffer = (uint16_t*)buffer;
	while(size > 0) {
		outw(ata_base[id] + ATA_DATA, *wbuffer);
		wbuffer++;
		size-=2;
	}
}

static int ata_begin(int id, int command, int nblocks, int offset) {
	int base = ata_base[id];
	int sector, clow, chigh, flags;

	flags = ATA_FLAGS_ECC | ATA_FLAGS_LBA | ATA_FLAGS_SEC;
	if(id % 2) flags |= ATA_FLAGS_SLV;

	sector = (offset >> 0) & 0xff;
	clow = (offset >> 8) & 0xff;
	chigh = (offset >> 16) & 0xff;
	flags |= (offset >> 24) & 0x0f;

	if(!ata_wait(id, ATA_STATUS_BSY, 0)) return 0;
	outb(base + ATA_FDH, flags);
	int ready;
	if(command == ATAPI_COMMAND_IDENTIFY) ready = ata_wait(id, ATA_STATUS_BSY,0);
	else ready = ata_wait(id, ATA_STATUS_BSY | ATA_STATUS_RDY, ATA_STATUS_RDY);

	if(!ready) return 0;

	outb(base + ATA_CONTROL, 0);
	outb(base + ATA_COUNT, nblocks);
	outb(base + ATA_SECTOR, sector);
	outb(base + ATA_CYL_LO, clow);
	outb(base + ATA_CYL_HI, chigh);
	outb(base + ATA_FDH, flags);
	outb(base + ATA_COMMAND, command);

	return 1;
}

static int ata_read_unlocked(int id, void *buffer, int nblocks, int offset) {
	int i;
	if(!ata_begin(id,ATA_COMMAND_READ,nblocks,offset)) return 0;
	for(i = 0;i < nblocks; i++) {
		if(!ata_wait(id, ATA_STATUS_DRQ, ATA_STATUS_DRQ)) return 0;
		ata_pio_read(id,buffer, ATA_BLOCKSIZE);
		buffer = ((char*)buffer) + ATA_BLOCKSIZE;
		offset++;
	}
	if(!ata_wait(id, ATA_STATUS_BSY, 0)) return 0;
	return nblocks;
}

int ata_read(int id, void *buffer, int nblocks, int offset) {
	int result;
	result = ata_read_unlocked(id, buffer, nblocks, offset);
	return result;
}

int ata_read_bytes(int id, void *buffer, int nbytes, int offset)
{
	int nblocks=nbytes/drives[id].block_size;
	if(nbytes % drives[id].block_size)
		nblocks++;
	int result = ata_read(id, buffer, nblocks, offset / drives[id].block_size);
	return result;
}
static int atapi_begin(int id, void *data, int length) {
	int base = ata_base[id];
	int flags;

	flags = ATA_FLAGS_ECC | ATA_FLAGS_LBA | ATA_FLAGS_SEC;
	if(id%2) flags |= ATA_FLAGS_SLV;
	if(!ata_wait(id, ATA_STATUS_BSY,0)) return 0;
	outb(base+ATA_FDH, flags);

	if(!ata_wait(id, ATA_STATUS_BSY,0)) return 0;

	outb(base+ ATAPI_FEATURE, 0);
	outb(base+ ATAPI_IRR, 0);
	outb(base+ ATAPI_SAMTAG, 0);
	outb(base + ATAPI_COUNT_LO, length & 0xff);
	outb(base + ATAPI_COUNT_HI, length >> 8);
	outb(base + ATA_COMMAND, ATAPI_COMMAND_PACKET);

	if(!ata_wait(id, ATA_STATUS_BSY | ATA_STATUS_DRQ, ATA_STATUS_DRQ)) {}
	ata_pio_write(id, data, length);

	return 1;
}

static int atapi_read_unlocked(int id, void *buffer, int nblocks, int offset) {
	uint8_t packet[12];
	int length = sizeof(packet);
	int i;

	packet[0] = SCSI_READ10;
	packet[1] = 0;
	packet[2] = offset >>24;
	packet[3] = offset >>16;
	packet[4] = offset >>8;
	packet[5] = offset >>0;
	packet[6] = 0;
	packet[7] = nblocks >>8;
	packet[8] = nblocks >>0;
	packet[9] = 0;
	packet[10] = 0;
	packet[11] = 0;

	if(!atapi_begin(id,packet,length)) return 0;

	for(i = 0;i < nblocks; i++) {
		if(!ata_wait(id, ATA_STATUS_DRQ, ATA_STATUS_DRQ)) return 0;
		ata_pio_read(id, buffer, ATAPI_BLOCKSIZE);
		buffer = ((char*)buffer) + ATAPI_BLOCKSIZE;
		offset++;
	}

	return nblocks;
}

int atapi_read(int id, void *buffer, int nblocks, int offset) {

	int result;
	result = atapi_read_unlocked(id, buffer, nblocks, offset);
	return result;
}

static int ata_write_unlocked(int id, const void *buffer, int nblocks, int offset) {
	int i;
	if(!ata_begin(id, ATA_COMMAND_WRITE, nblocks, offset)) return 0;

	for(i = 0; i < nblocks; i++) {
		if(!ata_wait(id, ATA_STATUS_DRQ, ATA_STATUS_DRQ)) return 0;
		ata_pio_write(id, buffer, ATA_BLOCKSIZE);
		buffer = ((char*)buffer) + ATA_BLOCKSIZE;
		offset++;
	}
	if(!ata_wait(id, ATA_STATUS_BSY, 0)) return 0;
	return nblocks;
}

int ata_write(int id, void *buffer, int nblocks, int offset) {
	int result;
	result = ata_write_unlocked(id, buffer, nblocks, offset);
	return result;
}
int ata_write_bytes(int id, void *buffer, int nbytes, int offset)
{
	return ata_write(id, buffer, nbytes*drives[id].block_size, offset);
}
static int ata_identify(int id, int command, void *buffer) {
	if(!ata_begin(id, command, 0, 0)) return 0;
	if(!ata_wait(id, ATA_STATUS_DRQ, ATA_STATUS_DRQ)) return 0;
	ata_pio_read(id, buffer, 512);
	return 1;
}

int ata_probe( int id, int *nblocks, int *blocksize, char *name ) {
	uint16_t buffer[256];
	char *cbuffer = (char*)buffer;

	uint8_t t = inb(ata_base[id] + ATA_STATUS);
	if(t == 0xff) {
		printk("ATA probing: nothing attached on drive %u\n", id);
		drives[id].name="Not attached!";
		drives[id].block_size=0;
		drives[id].size=0;
		drives[id].attached=0;
		return 0;
	}
	ata_reset(id);
	memset(cbuffer,0,512);
	if(ata_identify(id, ATA_COMMAND_IDENTIFY, cbuffer)) {
		*nblocks = buffer[1] * buffer[3] * buffer[6];
		*blocksize = 512;
 	} else if(ata_identify(id, ATAPI_COMMAND_IDENTIFY, cbuffer)) {
		*nblocks = 337920;
		*blocksize = 2048;
	} else {
		printk("ATA probing: identify command failed on drive %u\n", id);
		drives[id].name="Identify command failed! (Maybe nothing attached?)";
		drives[id].block_size=0;
		drives[id].size=0;
		drives[id].attached=0;
		return 0;
	}

	uint32_t i;
	for(i = 0; i < 512; i += 2) {
		t = cbuffer[i];
		cbuffer[i] = cbuffer[i + 1];
		cbuffer[i + 1] = t;
	}

	cbuffer[256]=0;
	strcpy(name, &cbuffer[54]);
	name[40] = 0;
	printk("ATA probing: saving info to drive list, found disk on drive %u: %d MB.\n", id, (int)(*nblocks)*(*blocksize)/1024/1024);
	printk("ATA device #%d: type: %s, size: %d MB, name: %s\n", id, (*blocksize)==512 ? "ATA disk" : "ATAPI CDROM", (int)(*nblocks)*(*blocksize)/1024/1024, name);
	drives[id].name=name;
	drives[id].block_size=*blocksize;
	drives[id].size=*nblocks * *blocksize;
	return 1;
}

void ata_init() {
	printk("Starting ATA initialization. Probing devices...\n");
	int i;
	int nblocks;
	int blocksizes[4];
	char disk_names[40][4];

	/*interrupt_register(ATA_IRQ0, ata_interrupt);
	interrupt_enable(ATA_IRQ0);

	interrupt_register(ATA_IRQ1, ata_interrupt);
	interrupt_enable(ATA_IRQ1);*/

	for(i = 0; i < 4; i++)ata_probe(i, &nblocks, &blocksizes[i], disk_names[i]);
	///printk("ATA device block sizes:\n\t%u, %u, %u, %u.\n", drives[0].block_size, blocksizes[1], blocksizes[2], blocksizes[3]);
}
