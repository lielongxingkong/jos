#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#define PCI_DEVICE_ID_E1000_82540EM	0x100e
#define PCI_VENDOR_ID_INTEL		0x8086

int pci_e1000_attach(struct pci_func *f);

#endif	// JOS_KERN_E1000_H
