#include <inc/string.h>
#include <inc/error.h>
#include <inc/assert.h>
#include <kern/pmap.h>
#include <kern/pci.h>
#include <kern/pcireg.h>
#include <kern/e1000.h>

// LAB 6: Your driver code here

volatile uint32_t *e1000_va;

int pci_e1000_attach(struct pci_func *f)
{
	pci_conf_write(f, PCI_COMMAND_STATUS_REG,
		       PCI_COMMAND_IO_ENABLE |
		       PCI_COMMAND_MEM_ENABLE |
		       PCI_COMMAND_MASTER_ENABLE);

	uint32_t bar_width;
	uint32_t bar;
	for (bar = PCI_MAPREG_START; bar < PCI_MAPREG_END;
	     bar += bar_width)
	{
		uint32_t oldv = pci_conf_read(f, bar);

		bar_width = 4;
		pci_conf_write(f, bar, 0xffffffff);
		uint32_t rv = pci_conf_read(f, bar);

		if (rv == 0)
			continue;

		int regnum = PCI_MAPREG_NUM(bar);
		uint32_t base, size;
		if (PCI_MAPREG_TYPE(rv) != PCI_MAPREG_TYPE_MEM)
			continue;

		if (PCI_MAPREG_MEM_TYPE(rv) == PCI_MAPREG_MEM_TYPE_64BIT) {
			bar_width = 8;
			size = PCI_MAPREG_MEM64_SIZE(rv);
			base = PCI_MAPREG_MEM64_ADDR(oldv);

		} else {
			size = PCI_MAPREG_MEM_SIZE(rv);
			base = PCI_MAPREG_MEM_ADDR(oldv);
		}

		pci_conf_write(f, bar, oldv);
		f->reg_base[regnum] = base;
		f->reg_size[regnum] = size;

		e1000_va = mmio_map_region(base, size);
		cprintf("E1000 %02x:%02x.%d (%04x:%04x) enabled\n",
			f->bus->busno, f->dev, f->func,
			PCI_VENDOR(f->dev_id), PCI_PRODUCT(f->dev_id));
		// TODO only one e1000 supported
		return 1;
	}
	return 0;
}
