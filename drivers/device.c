#include <asm/string.h>
#include <eduos/device.h>
#include <eduos/stdio.h>
#include <eduos/stdlib.h>

device_t *devices = 0;
uint8_t lastid = 0;

void device_print_out() {
    for(int i = 0; i < lastid; i++) {
        kprintf("id: %d, unique: %d, %s, %s\n", i, devices[i].unique_id,
            devices[i].dev_type == DEVICE_CHAR ?"CHAR":"BLOCK", devices[i].name);
    }
}

void device_init() {
    devices = kmalloc(sizeof(device_t) * MAX_DEVICE_NUM);
    memset(devices, 0, sizeof(device_t) * MAX_DEVICE_NUM);
    lastid = 0;
    kprintf("Device Manager initialized.\n");
}

int device_add(device_t* dev) {
    memcpy(devices + lastid, dev, sizeof(device_t));
    kprintf("Registered Device %s (%d) as Device#%d\n", dev->name, dev->unique_id, lastid);
    lastid++;
    return lastid - 1;
}

device_t *device_get_by_id(uint32_t id)
{
    for(int i = 0;i < 64; i++)
    {
        if(devices[i].unique_id == id) return &devices[i];
    }
    return 0;
}

int device_getnumber()
{
    return lastid;
}

device_t *device_get(uint32_t id)
{
    return &devices[id];
}