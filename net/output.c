#include "ns.h"

int debug = 0;
extern union Nsipc nsipcbuf;

void
output(envid_t ns_envid)
{
	binaryname = "ns_output";

	// LAB 6: Your code here:
	// 	- read a packet from the network server
	//	- send the packet to the device driver

	int whom, perm, r;
	struct jif_pkt *pkt;

	while(1) {
		r = ipc_recv((int32_t *) &whom, &nsipcbuf, &perm);
		pkt = &nsipcbuf.pkt;
		if (debug)
			cprintf("ns req %d from %08x [pkt %08x: %s]\n",
				r, whom, pkt->jp_len, pkt->jp_data);
		if (r != NSREQ_OUTPUT)
			continue;
		r = sys_transmit(pkt->jp_data, pkt->jp_len);
	}

}
