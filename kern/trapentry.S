/* See COPYRIGHT for copyright information. */

#include <inc/memlayout.h>

/*
 * Lab 3: Your code here for _alltraps
 */

.globl _alltraps
_alltraps:
	pushl	%ds
	pushl	%es
	pushal
	movl	$GD_KD, %eax
	movl	%eax, %ds
	movl	%eax, %es
	pushl	%esp
	call	trap
	addl	$4, %esp

