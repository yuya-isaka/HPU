	.file	"random.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB54:
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
.LFE54:
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
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"\n\nBind time %lf[ms]\n\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB53:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rbp
	call	clock@PLT
	movl	$32, %edx
	movl	$1024, %esi
	movq	%rbp, %rdi
	movl	$123456789, x.4591(%rip)
	movq	%rax, %rbx
	movl	$362436069, y.4592(%rip)
	movl	$521288629, z.4593(%rip)
	movl	$88675123, w.4594(%rip)
	call	makeArrayInt
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L20:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L21:
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L22:
	addq	$1, %rsi
.L24:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L21
	call	xor128.part.0
	movl	%eax, %r9d
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L22
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L20
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
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L28
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L28:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE53:
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
