#include <asm/ide.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <eduos/device.h>
#include <eduos/stdio.h>
#include <eduos/string.h>

#define ATA_PRIMARY_IO 0x1F0
#define ATA_SECONDARY_IO 0x170

#define ATA_PRIMARY_DCR_AS 0x3F6
#define ATA_SECONDARY_DCR_AS 0x376

#define ATA_IRQ_OFFSET 0x20
#define ATA_PRIMARY_IRQ 14
#define ATA_SECONDARY_IRQ 15

#define ATA_BUFFER_SIZE 2048

uint8_t ata_pm = 0; /* Primary master exists? */
uint8_t ata_ps = 0; /* Primary Slave exists? */
uint8_t ata_sm = 0; /* Secondary master exists? */
uint8_t ata_ss = 0; /* Secondary slave exists? */

uint8_t ide_buf[ATA_BUFFER_SIZE];

void ide_select_drive(uint8_t bus, uint8_t i)
{
	if(bus == ATA_PRIMARY)
		if(i == ATA_MASTER)
			outportb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outportb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xB0);
	else
		if(i == ATA_MASTER)
			outportb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outportb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xB0);
}

void ide_primary_irq(struct state *s)
{
    kprintf("primary irq fired!!\n");
	// IRQ_START;
	// send_eoi(ATA_PRIMARY_IRQ);
	// IRQ_END;
	return;
}

void ide_secondary_irq(struct state *s)
{
    kprintf("second irq fired!!\n");
	// IRQ_START;
	// send_eoi(ATA_SECONDARY_IRQ);
	// IRQ_END;
}

uint8_t ide_identify(uint8_t bus, uint8_t drive)
{
	uint16_t io = 0;
	ide_select_drive(bus, drive);
	if(bus == ATA_PRIMARY) io = ATA_PRIMARY_IO;
	else io = ATA_SECONDARY_IO;
	/* ATA specs say these values must be zero before sending IDENTIFY */
	outportb(io + ATA_REG_SECCOUNT0, 0);
	outportb(io + ATA_REG_LBA0, 0);
	outportb(io + ATA_REG_LBA1, 0);
	outportb(io + ATA_REG_LBA2, 0);
	/* Now, send IDENTIFY */
	outportb(io + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
	kprintf("Sent IDENTIFY\n");
	/* Now, read status port */
	uint8_t status = inportb(io + ATA_REG_STATUS);
	if(status)
	{
		/* Now, poll untill BSY is clear. */
		while(inportb(io + ATA_REG_STATUS) & ATA_SR_BSY != 0) ;
pm_stat_read:		status = inportb(io + ATA_REG_STATUS);
		if(status & ATA_SR_ERR)
		{
			kprintf("%s%s has ERR set. Disabled.\n", bus==ATA_PRIMARY?"Primary":"Secondary", drive==ATA_PRIMARY?" master":" slave");
			return 0;
		}
		while(!(status & ATA_SR_DRQ)) goto pm_stat_read;
		kprintf("%s%s is online.\n", bus==ATA_PRIMARY?"Primary":"Secondary", drive==ATA_PRIMARY?" master":" slave");
		/* Now, actually read the data */
		// set_task(0);
		for(int i = 0; i<256; i++)
		{
			*(uint16_t *)(ide_buf + i*2) = inportw(io + ATA_REG_DATA);
		}
		// set_task(1);
		return 1;
	}
	return 0;
}

void ide_400ns_delay(uint16_t io)
{
	for(int i = 0;i < 4; i++)
		inportb(io + ATA_REG_ALTSTATUS);
}

void ide_poll(uint16_t io)
{
	
	for(int i=0; i< 4; i++)
		inportb(io + ATA_REG_ALTSTATUS);

retry:;
	uint8_t status = inportb(io + ATA_REG_STATUS);
	//kprintf("testing for BSY\n");
	if(status & ATA_SR_BSY) goto retry;
	//kprintf("BSY cleared\n");
retry2:	status = inportb(io + ATA_REG_STATUS);
	if(status & ATA_SR_ERR)
	{
		kprintf("ERR set, device failure!\n");
	}
	//kprintf("testing for DRQ\n");
	if(!(status & ATA_SR_DRQ)) goto retry2;
	//kprintf("DRQ set, ready to PIO!\n");
	return;
}

uint8_t ata_read_one(uint8_t *buf, uint32_t lba, device_t *dev) {
	//lba &= 0x00FFFFFF; // ignore topmost byte
	/* We only support 28bit LBA so far */
	uint8_t drive = ((ide_private_data *)(dev->priv))->drive;
	uint16_t io = 0;
	switch(drive)
	{
		case (ATA_PRIMARY << 1 | ATA_MASTER):
			io = ATA_PRIMARY_IO;
			drive = ATA_MASTER;
			break;
		case (ATA_PRIMARY << 1 | ATA_SLAVE):
			io = ATA_PRIMARY_IO;
			drive = ATA_SLAVE;
			break;
		case (ATA_SECONDARY << 1 | ATA_MASTER):
			io = ATA_SECONDARY_IO;
			drive = ATA_MASTER;
			break;
		case (ATA_SECONDARY << 1 | ATA_SLAVE):
			io = ATA_SECONDARY_IO;
			drive = ATA_SLAVE;
			break;
		default:
			kprintf("FATAL: unknown drive!\n");
			return 0;
	}

	//kprintf("io=0x%x %s\n", io, drive==ATA_MASTER?"Master":"Slave");
	uint8_t cmd = (drive==ATA_MASTER?0xE0:0xF0);
	uint8_t slavebit = (drive == ATA_MASTER?0x00:0x01);
	/*kprintf("LBA = 0x%x\n", lba);
	kprintf("LBA>>24 & 0x0f = %d\n", (lba >> 24)&0x0f);
	kprintf("(uint8_t)lba = %d\n", (uint8_t)lba);
	kprintf("(uint8_t)(lba >> 8) = %d\n", (uint8_t)(lba >> 8));
	kprintf("(uint8_t)(lba >> 16) = %d\n", (uint8_t)(lba >> 16));*/
	//outportb(io + ATA_REG_HDDEVSEL, cmd | ((lba >> 24)&0x0f));
	outportb(io + ATA_REG_HDDEVSEL, (cmd | (uint8_t)((lba >> 24 & 0x0F))));
	//mprint("issued 0x%x to 0x%x\n", (cmd | (lba >> 24)&0x0f), io + ATA_REG_HDDEVSEL);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + 1, 0x00);
	//mprint("issued 0x%x to 0x%x\n", 0x00, io + 1);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + ATA_REG_SECCOUNT0, 1);
	//mprint("issued 0x%x to 0x%x\n", (uint8_t) numsects, io + ATA_REG_SECCOUNT0);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + ATA_REG_LBA0, (uint8_t)((lba)));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba)), io + ATA_REG_LBA0);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba) >> 8), io + ATA_REG_LBA1);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));
	//mprint("issued 0x%x to 0x%x\n", (uint8_t)((lba) >> 16), io + ATA_REG_LBA2);
	//for(int k = 0; k < 10000; k++) ;
	outportb(io + ATA_REG_COMMAND, ATA_CMD_READ_PIO);
	//mprint("issued 0x%x to 0x%x\n", ATA_CMD_READ_PIO, io + ATA_REG_COMMAND);

	ide_poll(io);

	// set_task(0);
	for(int i = 0; i < 256; i++)
	{
		uint16_t data = inportw(io + ATA_REG_DATA);
		*(uint16_t *)(buf + i * 2) = data;
	}
	ide_400ns_delay(io);
	// set_task(1);
	return 1;
}

uint8_t ata_read(uint8_t *buf, uint32_t lba, uint32_t numsects, void *dev) {
	for(int i = 0; i < numsects; i++)
	{
		ata_read_one(buf, lba + i, (device_t*)dev);
		buf += 512;
	}
	return 0;
}

void ata_probe()
{
	/* First check the primary bus,
	 * and inside the master drive.
	 */
	
	if(ide_identify(ATA_PRIMARY, ATA_MASTER))
	{
		ata_pm = 1;
		device_t dev;
		ide_private_data *priv = (ide_private_data *)kmalloc(sizeof(ide_private_data));
		/* Now, process the IDENTIFY data */
		/* Model goes from W#27 to W#46 */
		char str[40] = {0};
		for(int i = 0; i < 39; i += 2)
		{
			str[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			str[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}
		str[39] = 0;
		memcpy(dev.name, str, 40);
		dev.unique_id = 32;
		dev.dev_type = DEVICE_BLOCK;
		priv->drive = (ATA_PRIMARY << 1) | ATA_MASTER;
		priv->commandSets = *((unsigned int *)(ide_buf + ATA_IDENT_COMMANDSETS));
		if (priv->commandSets  & (1 << 26)) {
			priv->size = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA_EXT));
		} else {
			priv->size = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA));
		}
		dev.priv = priv;
		dev.read = ata_read;
		device_add(&dev);
		kprintf("Device: %s\n", str);
		// kprintf("Device size = %d\n", priv->size * 512 / 1024 / 1024);
	}
	if (ide_identify(ATA_PRIMARY, ATA_SLAVE)) {
		ata_ps = 1;
		device_t dev;
		ide_private_data *priv = (ide_private_data *)kmalloc(sizeof(ide_private_data));
		/* Now, process the IDENTIFY data */
		/* Model goes from W#27 to W#46 */
		char str[40] = {0};
		for(int i = 0; i < 39; i += 2)
		{
			str[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			str[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}
		str[39] = 0;
		memcpy(dev.name, str, 40);
		dev.unique_id = 33;
		dev.dev_type = DEVICE_BLOCK;
		priv->drive = (ATA_PRIMARY << 1) | ATA_SLAVE;
		priv->commandSets = *((unsigned int *)(ide_buf + ATA_IDENT_COMMANDSETS));
		if (priv->commandSets  & (1 << 26)) {
			priv->size = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA_EXT));
		} else {
			priv->size = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA));
		}
		dev.priv = priv;
		dev.read = ata_read;
		device_add(&dev);
		kprintf("Device: %s\n", str);
	}
	// ide_identify(ATA_SECONDARY, ATA_MASTER);
	// ide_identify(ATA_SECONDARY, ATA_SLAVE);
}

void ide_init(void)
{
    memset(ide_buf, 0, ATA_BUFFER_SIZE);
    irq_install_handler(ATA_IRQ_OFFSET + ATA_PRIMARY_IRQ, ide_primary_irq);
    irq_install_handler(ATA_IRQ_OFFSET + ATA_SECONDARY_IRQ, ide_secondary_irq);
    ata_probe();
}