	.file	"bind.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB55:
	.cfi_startproc
	movl	x.4593(%rip), %eax
	movl	w.4596(%rip), %ecx
	movl	%eax, %edx
	sall	$11, %edx
	xorl	%eax, %edx
	movl	y.4594(%rip), %eax
	movl	%eax, x.4593(%rip)
	movl	z.4595(%rip), %eax
	movl	%ecx, z.4595(%rip)
	movl	%eax, y.4594(%rip)
	movl	%ecx, %eax
	shrl	$19, %eax
	xorl	%ecx, %eax
	xorl	%edx, %eax
	shrl	$8, %edx
	xorl	%edx, %eax
	movl	%eax, w.4596(%rip)
	ret
	.cfi_endproc
.LFE55:
	.size	xor128.part.0, .-xor128.part.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"leaks -q a.out"
	.section	.text.exit,"ax",@progbits
	.p2align 4
	.type	destructor, @function
destructor:
.LFB50:
	.cfi_startproc
	endbr64
	leaq	.LC0(%rip), %rdi
	jmp	system@PLT
	.cfi_endproc
.LFE50:
	.size	destructor, .-destructor
	.section	.fini_array,"aw"
	.align 8
	.quad	destructor
	.text
	.p2align 4
	.globl	makeArrayInt
	.type	makeArrayInt, @function
makeArrayInt:
.LFB51:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdi, %r13
	movslq	%esi, %rdi
	movl	$8, %esi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movslq	%edx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	calloc@PLT
	movq	%rax, 0(%r13)
	testl	%r12d, %r12d
	jle	.L4
	movq	%rax, %rbx
	leal	-1(%r12), %eax
	leaq	8(%rbx,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L6:
	movl	$4, %esi
	movq	%rbp, %rdi
	addq	$8, %rbx
	call	calloc@PLT
	movq	%rax, -8(%rbx)
	cmpq	%r12, %rbx
	jne	.L6
.L4:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
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
.LFE51:
	.size	makeArrayInt, .-makeArrayInt
	.p2align 4
	.globl	freeArrayInt
	.type	freeArrayInt, @function
freeArrayInt:
.LFB52:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	testl	%esi, %esi
	jle	.L11
	leal	-1(%rsi), %eax
	xorl	%ebx, %ebx
	leaq	8(,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L12:
	movq	0(%rbp), %rax
	movq	(%rax,%rbx), %rdi
	addq	$8, %rbx
	call	free@PLT
	cmpq	%r12, %rbx
	jne	.L12
.L11:
	movq	0(%rbp), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE52:
	.size	freeArrayInt, .-freeArrayInt
	.p2align 4
	.globl	xor128
	.type	xor128, @function
xor128:
.LFB53:
	.cfi_startproc
	endbr64
	testl	%edi, %edi
	jne	.L19
	jmp	xor128.part.0
	.p2align 4,,10
	.p2align 3
.L19:
	movl	$123456789, x.4593(%rip)
	xorl	%eax, %eax
	movl	$362436069, y.4594(%rip)
	movl	$521288629, z.4595(%rip)
	movl	$88675123, w.4596(%rip)
	ret
	.cfi_endproc
.LFE53:
	.size	xor128, .-xor128
	.section	.rodata.str1.1
.LC3:
	.string	"\n\nBind time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rbp
	call	clock@PLT
	movl	$10, %edi
	movq	%rax, %rbx
	call	srand@PLT
	movl	$32, %edx
	movl	$1024, %esi
	movq	%rbp, %rdi
	movl	$123456789, x.4593(%rip)
	movl	$362436069, y.4594(%rip)
	movl	$521288629, z.4595(%rip)
	movl	$88675123, w.4596(%rip)
	call	makeArrayInt
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L21:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L22:
	movq	8(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L23:
	addq	$1, %rsi
.L25:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L22
	call	xor128.part.0
	movl	%eax, %r9d
	movq	8(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L23
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L21
	leaq	16(%rsp), %r12
	movl	$32, %edx
	movl	$50000000, %esi
	xorl	%r14d, %r14d
	movq	%r12, %rdi
	call	makeArrayInt
	.p2align 4,,10
	.p2align 3
.L27:
	call	rand@PLT
	movl	%eax, %r13d
	call	rand@PLT
	movl	%r13d, %esi
	movq	8(%rsp), %rcx
	sarl	$31, %esi
	shrl	$22, %esi
	leal	0(%r13,%rsi), %edx
	andl	$1023, %edx
	subl	%esi, %edx
	movslq	%edx, %rdx
	movq	(%rcx,%rdx,8), %rdi
	cltd
	shrl	$22, %edx
	addl	%edx, %eax
	andl	$1023, %eax
	subl	%edx, %eax
	cltq
	movq	(%rcx,%rax,8), %rsi
	movq	16(%rsp), %rax
	movq	(%rax,%r14), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L26:
	movl	(%rdi,%rax), %edx
	xorl	(%rsi,%rax), %edx
	movl	%edx, (%rcx,%rax)
	addq	$4, %rax
	cmpq	$128, %rax
	jne	.L26
	addq	$8, %r14
	cmpq	$400000000, %r14
	jne	.L27
	movl	$50000000, %esi
	movq	%r12, %rdi
	call	freeArrayInt
	movl	$1024, %esi
	movq	%rbp, %rdi
	call	freeArrayInt
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	leaq	.LC3(%rip), %rsi
	subq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC1(%rip), %xmm0
	movl	$1, %eax
	mulsd	.LC2(%rip), %xmm0
	call	__printf_chk@PLT
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L33
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L33:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE54:
	.size	main, .-main
	.data
	.align 4
	.type	w.4596, @object
	.size	w.4596, 4
w.4596:
	.long	88675123
	.align 4
	.type	z.4595, @object
	.size	z.4595, 4
z.4595:
	.long	521288629
	.align 4
	.type	y.4594, @object
	.size	y.4594, 4
y.4594:
	.long	362436069
	.align 4
	.type	x.4593, @object
	.size	x.4593, 4
x.4593:
	.long	123456789
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.align 8
.LC2:
	.long	0
	.long	1083129856
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
