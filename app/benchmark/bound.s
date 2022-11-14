	.file	"bound.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB55:
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
.LFE55:
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
	.globl	bounding
	.type	bounding, @function
bounding:
.LFB53:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rbx
	movq	%rdi, %r11
	movq	%rsi, %r10
	leaq	(%rdi,%rsi,4), %rdi
	shrq	%rbx
	movl	$32, %r8d
	xorl	%r9d, %r9d
	movl	$-2147483648, %esi
	.p2align 4,,10
	.p2align 3
.L20:
	movq	%r11, %rax
	xorl	%edx, %edx
	testq	%r10, %r10
	je	.L22
	.p2align 4,,10
	.p2align 3
.L21:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L21
	movslq	%edx, %rdx
	leal	(%r9,%rsi), %eax
	cmpq	%rbx, %rdx
	cmova	%eax, %r9d
.L22:
	shrl	%esi
	subl	$1, %r8d
	jne	.L20
	movl	%r9d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE53:
	.size	bounding, .-bounding
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%u\n"
.LC3:
	.string	"\n\nBound time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$168, %rsp
	.cfi_def_cfa_offset 224
	movq	%fs:40, %rax
	movq	%rax, 152(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rbp
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
.L29:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L30:
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L31:
	addq	$1, %rsi
.L33:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L30
	call	xor128.part.0
	movl	%eax, %r9d
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L31
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L29
	leaq	8(%rsp), %r12
	movl	$50000000, %edx
	movl	$32, %esi
	xorl	%r13d, %r13d
	movq	%r12, %rdi
	call	makeArrayInt
	.p2align 4,,10
	.p2align 3
.L35:
	call	rand@PLT
	movq	8(%rsp), %r8
	cltd
	shrl	$22, %edx
	addl	%edx, %eax
	andl	$1023, %eax
	subl	%edx, %eax
	movq	(%rsp), %rdx
	cltq
	movq	(%rdx,%rax,8), %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L34:
	movl	(%rsi,%rax,4), %ecx
	movq	(%r8,%rax,8), %rdx
	addq	$1, %rax
	movl	%ecx, (%rdx,%r13)
	cmpq	$32, %rax
	jne	.L34
	addq	$4, %r13
	cmpq	$200000000, %r13
	jne	.L35
	xorl	%r14d, %r14d
	leaq	16(%rsp), %r13
.L40:
	movq	(%r8,%r14,8), %r11
	movl	$32, %r10d
	xorl	%r9d, %r9d
	movl	$-2147483648, %esi
	leaq	200000000(%r11), %rdi
	.p2align 4,,10
	.p2align 3
.L36:
	movq	%r11, %rax
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L37:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L37
	leal	(%r9,%rsi), %eax
	cmpl	$25000000, %edx
	cmovg	%eax, %r9d
	shrl	%esi
	subl	$1, %r10d
	jne	.L36
	movl	%r9d, 0(%r13,%r14,4)
	addq	$1, %r14
	cmpq	$32, %r14
	jne	.L40
	leaq	144(%rsp), %r15
	leaq	.LC0(%rip), %r14
.L41:
	movl	0(%r13), %edx
	movq	%r14, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %r13
	call	__printf_chk@PLT
	cmpq	%r13, %r15
	jne	.L41
	movl	$32, %esi
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
	movq	152(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L50
	addq	$168, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L50:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE54:
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
