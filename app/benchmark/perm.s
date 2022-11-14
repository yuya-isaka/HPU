	.file	"perm.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB56:
	.cfi_startproc
	movl	x.4591(%rip), %eax
	movl	w.4594(%rip), %ecx
	movl	%eax, %edx
	sall	$11, %edx
	xorl	%eax, %edx
	movl	y.4592(%rip), %eax
	movl	%eax, x.4591(%rip)
	movl	z.4593(%rip), %eax
	movl	%ecx, z.4593(%rip)
	movl	%eax, y.4592(%rip)
	movl	%ecx, %eax
	shrl	$19, %eax
	xorl	%ecx, %eax
	xorl	%edx, %eax
	shrl	$8, %edx
	xorl	%edx, %eax
	movl	%eax, w.4594(%rip)
	ret
	.cfi_endproc
.LFE56:
	.size	xor128.part.0, .-xor128.part.0
	.p2align 4
	.globl	makeArrayInt
	.type	makeArrayInt, @function
makeArrayInt:
.LFB50:
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
	jle	.L3
	movq	%rax, %rbx
	leal	-1(%r12), %eax
	leaq	8(%rbx,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L5:
	movl	$4, %esi
	movq	%rbp, %rdi
	addq	$8, %rbx
	call	calloc@PLT
	movq	%rax, -8(%rbx)
	cmpq	%r12, %rbx
	jne	.L5
.L3:
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
.LFE50:
	.size	makeArrayInt, .-makeArrayInt
	.p2align 4
	.globl	freeArrayInt
	.type	freeArrayInt, @function
freeArrayInt:
.LFB51:
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
	jle	.L10
	leal	-1(%rsi), %eax
	xorl	%ebx, %ebx
	leaq	8(,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L11:
	movq	0(%rbp), %rax
	movq	(%rax,%rbx), %rdi
	addq	$8, %rbx
	call	free@PLT
	cmpq	%r12, %rbx
	jne	.L11
.L10:
	movq	0(%rbp), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE51:
	.size	freeArrayInt, .-freeArrayInt
	.p2align 4
	.globl	xor128
	.type	xor128, @function
xor128:
.LFB52:
	.cfi_startproc
	endbr64
	testl	%edi, %edi
	jne	.L18
	jmp	xor128.part.0
	.p2align 4,,10
	.p2align 3
.L18:
	movl	$123456789, x.4591(%rip)
	xorl	%eax, %eax
	movl	$362436069, y.4592(%rip)
	movl	$521288629, z.4593(%rip)
	movl	$88675123, w.4594(%rip)
	ret
	.cfi_endproc
.LFE52:
	.size	xor128, .-xor128
	.p2align 4
	.globl	shifter_32
	.type	shifter_32, @function
shifter_32:
.LFB53:
	.cfi_startproc
	endbr64
	movl	%esi, %ecx
	movl	$1, %edx
	movl	(%rdi), %eax
	sall	%cl, %edx
	movl	$32, %ecx
	subl	$1, %edx
	subl	%esi, %ecx
	andl	%eax, %edx
	sall	%cl, %edx
	movl	%esi, %ecx
	movl	%edx, (%rdi)
	shrl	%cl, %eax
	ret
	.cfi_endproc
.LFE53:
	.size	shifter_32, .-shifter_32
	.p2align 4
	.globl	shifter_1024
	.type	shifter_1024, @function
shifter_1024:
.LFB54:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rsi, %r13
	movl	$4, %esi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	%ecx, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movl	%edx, %edi
	movq	%rdi, %r12
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	calloc@PLT
	movq	%rax, %rdi
	testl	%r12d, %r12d
	je	.L26
	movl	$1, %r9d
	movl	%ebp, %ecx
	leal	-1(%r12), %r8d
	xorl	%edx, %edx
	sall	%cl, %r9d
	movl	$32, %r10d
	movq	0(%r13), %r11
	leaq	(%rax,%r8,4), %r12
	subl	$1, %r9d
	subl	%ebp, %r10d
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L22:
	orl	%eax, -4(%rdi,%rdx,4)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	je	.L30
.L27:
	movq	%rax, %rdx
.L24:
	movl	(%r11,%rdx,4), %esi
	movl	%r10d, %ecx
	movl	%esi, %eax
	andl	%r9d, %eax
	sall	%cl, %eax
	movl	%ebp, %ecx
	shrl	%cl, %esi
	orl	%esi, (%rdi,%rdx,4)
	testq	%rdx, %rdx
	jne	.L22
	orl	%eax, (%r12)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	jne	.L27
.L30:
	movq	(%rbx), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L25:
	movl	(%rdi,%rdx,4), %eax
	movl	%eax, (%rcx,%rdx,4)
	movq	%rdx, %rax
	addq	$1, %rdx
	cmpq	%rax, %r8
	jne	.L25
.L26:
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
	jmp	free@PLT
	.cfi_endproc
.LFE54:
	.size	shifter_1024, .-shifter_1024
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"\n\nPermu time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB55:
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
	movl	$123456789, x.4591(%rip)
	movl	$362436069, y.4592(%rip)
	movl	$521288629, z.4593(%rip)
	movl	$88675123, w.4594(%rip)
	call	makeArrayInt
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L32:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L33:
	movq	8(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L34:
	addq	$1, %rsi
.L36:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L33
	call	xor128.part.0
	movl	%eax, %r9d
	movq	8(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L34
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L32
	leaq	16(%rsp), %r14
	movl	$32, %edx
	movl	$50000000, %esi
	xorl	%r13d, %r13d
	movq	%r14, %rdi
	call	makeArrayInt
	.p2align 4,,10
	.p2align 3
.L37:
	call	rand@PLT
	movl	%eax, %r12d
	call	rand@PLT
	movq	16(%rsp), %rdi
	cltd
	shrl	$27, %edx
	addq	%r13, %rdi
	addq	$8, %r13
	leal	(%rax,%rdx), %ecx
	andl	$31, %ecx
	subl	%edx, %ecx
	movl	%r12d, %edx
	sarl	$31, %edx
	shrl	$22, %edx
	leal	(%r12,%rdx), %eax
	andl	$1023, %eax
	subl	%edx, %eax
	movq	8(%rsp), %rdx
	cltq
	leaq	(%rdx,%rax,8), %rsi
	movl	$32, %edx
	call	shifter_1024
	cmpq	$400000000, %r13
	jne	.L37
	movl	$50000000, %esi
	movq	%r14, %rdi
	call	freeArrayInt
	movl	$1024, %esi
	movq	%rbp, %rdi
	call	freeArrayInt
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	leaq	.LC2(%rip), %rsi
	subq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC0(%rip), %xmm0
	movl	$1, %eax
	mulsd	.LC1(%rip), %xmm0
	call	__printf_chk@PLT
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L42
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
.L42:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE55:
	.size	main, .-main
	.data
	.align 4
	.type	w.4594, @object
	.size	w.4594, 4
w.4594:
	.long	88675123
	.align 4
	.type	z.4593, @object
	.size	z.4593, 4
z.4593:
	.long	521288629
	.align 4
	.type	y.4592, @object
	.size	y.4592, 4
y.4592:
	.long	362436069
	.align 4
	.type	x.4591, @object
	.size	x.4591, 4
x.4591:
	.long	123456789
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1093567616
	.align 8
.LC1:
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
