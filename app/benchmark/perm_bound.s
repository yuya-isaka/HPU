	.file	"perm_bound.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB57:
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
.LFE57:
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
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L25:
	movl	(%rdi,%rdx,4), %eax
	movl	%eax, (%rbx,%rdx,4)
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
	.p2align 4
	.globl	bounding
	.type	bounding, @function
bounding:
.LFB55:
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
.L32:
	movq	%r11, %rax
	xorl	%edx, %edx
	testq	%r10, %r10
	je	.L34
	.p2align 4,,10
	.p2align 3
.L33:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L33
	movslq	%edx, %rdx
	leal	(%r9,%rsi), %eax
	cmpq	%rbx, %rdx
	cmova	%eax, %r9d
.L34:
	shrl	%esi
	subl	$1, %r8d
	jne	.L32
	movl	%r9d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE55:
	.size	bounding, .-bounding
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%u\n"
.LC3:
	.string	"\n\nPermu time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB56:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$4096, %rsp
	orq	$0, (%rsp)
	subq	$200, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	leaq	-4296(%rbp), %r13
	call	clock@PLT
	movl	$10, %edi
	movq	%rax, -4320(%rbp)
	call	srand@PLT
	movl	$32, %edx
	movl	$1024, %esi
	movq	%r13, %rdi
	movl	$123456789, x.4591(%rip)
	movl	$362436069, y.4592(%rip)
	movl	$521288629, z.4593(%rip)
	movl	$88675123, w.4594(%rip)
	call	makeArrayInt
	xorl	%r10d, %r10d
.L41:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L42:
	movq	-4296(%rbp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L43:
	addq	$1, %rsi
.L45:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L42
	call	xor128.part.0
	movl	%eax, %r9d
	movq	-4296(%rbp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L43
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L41
	leaq	-4160(%rbp), %rbx
	leaq	-64(%rbp), %rdx
	movq	%rbx, %r15
	movq	%rbx, %rax
.L46:
	movl	$0, (%rax)
	addq	$4, %rax
	cmpq	%rdx, %rax
	jne	.L46
	movl	$50000000, -4308(%rbp)
	leaq	128(%rbx), %r14
.L54:
	call	rand@PLT
	movq	%rsp, %r12
	movl	%eax, -4328(%rbp)
	call	rand@PLT
	movq	%rsp, %rcx
	movl	-4328(%rbp), %edx
	cmpq	%rcx, %rsp
	je	.L48
.L71:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L71
.L48:
	addq	$-128, %rsp
	orq	$0, 120(%rsp)
	movl	%eax, %esi
	movq	%rsp, %rdi
	sarl	$31, %esi
	movq	%rdi, -4328(%rbp)
	shrl	$27, %esi
	leal	(%rax,%rsi), %ecx
	andl	$31, %ecx
	subl	%esi, %ecx
	movl	%edx, %esi
	sarl	$31, %esi
	shrl	$22, %esi
	leal	(%rdx,%rsi), %eax
	movq	-4296(%rbp), %rdx
	andl	$1023, %eax
	subl	%esi, %eax
	cltq
	leaq	(%rdx,%rax,8), %rsi
	movl	$32, %edx
	call	shifter_1024
	movq	-4328(%rbp), %rdi
	movq	%r14, %rsi
	xorl	%r11d, %r11d
	.p2align 4,,10
	.p2align 3
.L50:
	movl	(%rdi,%r11,4), %r10d
	leaq	-128(%rsi), %rdx
	movl	$1, %ecx
	.p2align 4,,10
	.p2align 3
.L52:
	movl	%r10d, %eax
	andl	%ecx, %eax
	cmpl	$1, %eax
	sbbl	%eax, %eax
	addl	%ecx, %ecx
	andl	$2, %eax
	subl	$1, %eax
	addl	%eax, (%rdx)
	addq	$4, %rdx
	cmpq	%rsi, %rdx
	jne	.L52
	addq	$1, %r11
	leaq	128(%rdx), %rsi
	cmpq	$32, %r11
	jne	.L50
	subl	$1, -4308(%rbp)
	movq	%r12, %rsp
	jne	.L54
	leaq	-4288(%rbp), %r12
	movq	%r12, %rax
.L55:
	movl	$0, (%rax)
	addq	$4, %rax
	cmpq	%rax, %rbx
	jne	.L55
	movq	%r12, %rsi
.L56:
	movl	(%rsi), %edx
	xorl	%ecx, %ecx
.L57:
	movl	(%r15,%rcx,4), %eax
	shrl	$31, %eax
	sall	%cl, %eax
	addq	$1, %rcx
	addl	%eax, %edx
	cmpq	$32, %rcx
	jne	.L57
	movl	%edx, (%rsi)
	addq	$4, %rsi
	movq	%r14, %r15
	cmpq	%rsi, %rbx
	je	.L72
	subq	$-128, %r14
	jmp	.L56
.L72:
	leaq	.LC0(%rip), %r14
.L58:
	movl	(%r12), %edx
	movq	%r14, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %r12
	call	__printf_chk@PLT
	cmpq	%r12, %rbx
	jne	.L58
	movl	$1024, %esi
	movq	%r13, %rdi
	call	freeArrayInt
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	subq	-4320(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC1(%rip), %xmm0
	movl	$1, %eax
	leaq	.LC3(%rip), %rsi
	mulsd	.LC2(%rip), %xmm0
	call	__printf_chk@PLT
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L73
	leaq	-40(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L73:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE56:
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
