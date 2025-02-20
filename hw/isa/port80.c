#include "qemu/osdep.h"
#include "hw/isa/isa.h"
#include "hw/irq.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qemu/error-report.h"
#include "qom/object.h"

#define TYPE_PORT80 "port80"
OBJECT_DECLARE_SIMPLE_TYPE(Port80State, PORT80)

struct Port80State {
    ISADevice parent_obj;
    MemoryRegion io;
};

static void port80_ioport_write(void *opaque, hwaddr addr, uint64_t data, unsigned size)
{
    qemu_log("Write to port 0x80: 0x%02x\n", (uint8_t)data);
}

static const MemoryRegionOps port80_io_ops = {
    .write = port80_ioport_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void port80_realize(DeviceState *dev, Error **errp)
{
    Port80State *s = PORT80(dev);
    memory_region_init_io(&s->io, OBJECT(s), &port80_io_ops, s, "port80-io", 1);
    isa_register_ioport(ISA_DEVICE(dev), &s->io, 0x80);
}

/*
static void port80_init(Object *obj)
{
    // Initialization code if needed
}
*/

static void port80_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->realize = port80_realize;
}

static const TypeInfo port80_info = {
    .name = TYPE_PORT80,
    .parent = TYPE_ISA_DEVICE,
    .instance_size = sizeof(Port80State),
  //  .instance_init = port80_init,
    .class_init = port80_class_init,
};

static void port80_register_types(void)
{
    type_register_static(&port80_info);
}

type_init(port80_register_types);
