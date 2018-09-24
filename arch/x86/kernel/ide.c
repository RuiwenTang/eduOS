#include <asm/ide.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <eduos/stdio.h>
#include <eduos/string.h>

#define ATA_PRIMARY_IO 0x1F0
#define ATA_SECONDARY_IO 0x170

#define ATA_PRIMARY_DCR_AS 0x3F6
#define ATA_SECONDARY_DCR_AS 0x376

#define ATA_PRIMARY_IRQ 14
#define ATA_SECONDARY_IRQ 15

#define ATA_BUFFER_SIZE 512

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
	IRQ_START;
	send_eoi(ATA_PRIMARY_IRQ);
	IRQ_END;
}

void ide_secondary_irq(struct state *s)
{
    kprintf("second irq fired!!\n");
	IRQ_START;
	send_eoi(ATA_SECONDARY_IRQ);
	IRQ_END;
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
	}
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

void ata_probe()
{
	/* First check the primary bus,
	 * and inside the master drive.
	 */
	
	if(ide_identify(ATA_PRIMARY, ATA_MASTER))
	{
		ata_pm = 1;
		// device_t *dev = (device_t *)malloc(sizeof(device_t));
		ide_private_data *priv = (ide_private_data *)kmalloc(sizeof(ide_private_data));
		/* Now, process the IDENTIFY data */
		/* Model goes from W#27 to W#46 */
		char str[40] = {0};
		for(int i = 0; i < 40; i += 2)
		{
			str[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			str[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}
		// dev->name = str;
		// dev->unique_id = 32;
		// dev->dev_type = DEVICE_BLOCK;
		// priv->drive = (ATA_PRIMARY << 1) | ATA_MASTER;
		// dev->priv = priv;
		// dev->read = ata_read;
		// device_add(dev);
		kprintf("Device: %s\n", str);
	}
	ide_identify(ATA_PRIMARY, ATA_SLAVE);
	/*ide_identify(ATA_SECONDARY, ATA_MASTER);
	ide_identify(ATA_SECONDARY, ATA_SLAVE);*/
}

void ide_init(void)
{
    memset(ide_buf, 0, ATA_BUFFER_SIZE);
    irq_install_handler(ATA_PRIMARY_IRQ, ide_primary_irq);
    irq_install_handler(ATA_SECONDARY_IRQ, ide_secondary_irq);
    ata_probe();
}