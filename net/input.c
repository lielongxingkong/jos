#include "ns.h"

extern int debug;
extern union Nsipc nsipcbuf;

void
input(envid_t ns_envid)
{
	binaryname = "ns_input";

	// LAB 6: Your code here:
	// 	- read a packet from the device driver
	//	- send it to the network server
	// Hint: When you IPC a page to the network server, it will be
	// reading from it for a while, so don't immediately receive
	// another packet in to the same physical page.

	int r;
	struct jif_pkt *pkt;

	while(1) {
	
		pkt = &nsipcbuf.pkt;
		if ((r = sys_page_alloc(0, pkt, PTE_P|PTE_U|PTE_W)) < 0)
			panic("sys_page_alloc: %e", r);

		if ((r = sys_receive(pkt->jp_data, PGSIZE)) < 0)
			panic("sys_receive: %e", r);
		pkt->jp_len = r;
		ipc_send(ns_envid, NSREQ_INPUT, &nsipcbuf, PTE_P|PTE_W|PTE_U);
		sys_page_unmap(0, pkt);
		//if (debug)
	//		cprintf("ns send %d to %08x [pkt %08x: %s]\n",
	//			NSREQ_INPUT, ns_envid, pkt->jp_len, pkt->jp_data);
		sys_yield();
	}

}
