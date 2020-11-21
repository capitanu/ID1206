	.file	"tlb.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"#pages\t proc\t\t sum"
.LC2:
	.string	"%d\t %.6f\t %ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	.LC0(%rip), %rdi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	$1048576, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movl	$1, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	puts@PLT
	.p2align 4,,10
	.p2align 3
.L2:
	call	clock@PLT
	movq	%rax, %r13
	movl	%ebp, %eax
	cltd
	idivl	%ebx
	imulq	%rbx, %rax
	movq	%rax, %r12
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	%ebx, %esi
	movq	%r12, %rdx
	subq	%r13, %rax
	leaq	.LC2(%rip), %rdi
	addq	$1, %rbx
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	divsd	.LC1(%rip), %xmm0
	call	printf@PLT
	cmpq	$16, %rbx
	jne	.L2
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
