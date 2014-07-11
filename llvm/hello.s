	.def	 _main;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	_main
	.align	16, 0x90
_main:                                  # @main
# BB#0:
	pushl	%ebp
Ltmp0:
	movl	%esp, %ebp
Ltmp1:
	subl	$8, %esp
Ltmp2:
	calll	___main
	movl	$L_.str, (%esp)
	calll	_puts
	xorl	%eax, %eax
	addl	$8, %esp
	popl	%ebp
	ret

	.data
L_.str:                                 # @.str
	.asciz	 "hello world\n"


