// hello, world
#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	char a[10] = "qwertyuio";
	cprintf("hello, world\n");
	cprintf("i am environment %08x\n", thisenv->env_id);
	sys_cputs(a, 5);
	sys_transmit(a, 5);
}
