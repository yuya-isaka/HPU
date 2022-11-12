	.file	"addition.c"
	.text
	.p2align 4
	.type	xor128.part.0, @function
xor128.part.0:
.LFB60:
	.cfi_startproc
	movl	x.4610(%rip), %eax
	movl	w.4613(%rip), %ecx
	movl	%eax, %edx
	sall	$11, %edx
	xorl	%eax, %edx
	movl	y.4611(%rip), %eax
	movl	%eax, x.4610(%rip)
	movl	z.4612(%rip), %eax
	movl	%ecx, z.4612(%rip)
	movl	%eax, y.4611(%rip)
	movl	%ecx, %eax
	shrl	$19, %eax
	xorl	%ecx, %eax
	xorl	%edx, %eax
	shrl	$8, %edx
	xorl	%edx, %eax
	movl	%eax, w.4613(%rip)
	ret
	.cfi_endproc
.LFE60:
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
	.globl	makeArray
	.type	makeArray, @function
makeArray:
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
	movl	$2, %esi
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
	.size	makeArray, .-makeArray
	.p2align 4
	.globl	freeArray
	.type	freeArray, @function
freeArray:
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
	.size	freeArray, .-freeArray
	.p2align 4
	.globl	makeArrayInt
	.type	makeArrayInt, @function
makeArrayInt:
.LFB53:
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
	jle	.L15
	movq	%rax, %rbx
	leal	-1(%r12), %eax
	leaq	8(%rbx,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L17:
	movl	$4, %esi
	movq	%rbp, %rdi
	addq	$8, %rbx
	call	calloc@PLT
	movq	%rax, -8(%rbx)
	cmpq	%r12, %rbx
	jne	.L17
.L15:
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
.LFE53:
	.size	makeArrayInt, .-makeArrayInt
	.p2align 4
	.globl	freeArrayInt
	.type	freeArrayInt, @function
freeArrayInt:
.LFB54:
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
	jle	.L22
	leal	-1(%rsi), %eax
	xorl	%ebx, %ebx
	leaq	8(,%rax,8), %r12
	.p2align 4,,10
	.p2align 3
.L23:
	movq	0(%rbp), %rax
	movq	(%rax,%rbx), %rdi
	addq	$8, %rbx
	call	free@PLT
	cmpq	%r12, %rbx
	jne	.L23
.L22:
	movq	0(%rbp), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE54:
	.size	freeArrayInt, .-freeArrayInt
	.p2align 4
	.globl	xor128
	.type	xor128, @function
xor128:
.LFB55:
	.cfi_startproc
	endbr64
	testl	%edi, %edi
	jne	.L30
	jmp	xor128.part.0
	.p2align 4,,10
	.p2align 3
.L30:
	movl	$123456789, x.4610(%rip)
	xorl	%eax, %eax
	movl	$362436069, y.4611(%rip)
	movl	$521288629, z.4612(%rip)
	movl	$88675123, w.4613(%rip)
	ret
	.cfi_endproc
.LFE55:
	.size	xor128, .-xor128
	.p2align 4
	.globl	shifter_32
	.type	shifter_32, @function
shifter_32:
.LFB56:
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
.LFE56:
	.size	shifter_32, .-shifter_32
	.p2align 4
	.globl	grab_bit
	.type	grab_bit, @function
grab_bit:
.LFB57:
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
.L33:
	movq	%r11, %rax
	xorl	%edx, %edx
	testq	%r10, %r10
	je	.L35
	.p2align 4,,10
	.p2align 3
.L34:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L34
	movslq	%edx, %rdx
	leal	(%r9,%rsi), %eax
	cmpq	%rbx, %rdx
	cmova	%eax, %r9d
.L35:
	shrl	%esi
	subl	$1, %r8d
	jne	.L33
	movl	%r9d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE57:
	.size	grab_bit, .-grab_bit
	.p2align 4
	.globl	shifter_1024
	.type	shifter_1024, @function
shifter_1024:
.LFB58:
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
	je	.L47
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
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L43:
	orl	%eax, -4(%rdi,%rdx,4)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	je	.L51
.L48:
	movq	%rax, %rdx
.L45:
	movl	(%r11,%rdx,4), %esi
	movl	%r10d, %ecx
	movl	%esi, %eax
	andl	%r9d, %eax
	sall	%cl, %eax
	movl	%ebp, %ecx
	shrl	%cl, %esi
	orl	%esi, (%rdi,%rdx,4)
	testq	%rdx, %rdx
	jne	.L43
	orl	%eax, (%r12)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	jne	.L48
.L51:
	movq	(%rbx), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L46:
	movl	(%rdi,%rdx,4), %eax
	movl	%eax, (%rcx,%rdx,4)
	movq	%rdx, %rax
	addq	$1, %rdx
	cmpq	%rax, %r8
	jne	.L46
.L47:
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
.LFE58:
	.size	shifter_1024, .-shifter_1024
	.section	.rodata.str1.1
.LC1:
	.string	"%u\n"
.LC4:
	.string	"\n\n  time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB59:
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
	movl	$123456789, x.4610(%rip)
	movl	$362436069, y.4611(%rip)
	movl	$521288629, z.4612(%rip)
	movl	$88675123, w.4613(%rip)
	call	makeArrayInt
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L53:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L54:
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	$88675123, (%rax,%rsi,4)
.L55:
	addq	$1, %rsi
.L57:
	movl	%r8d, %eax
	orl	%esi, %eax
	je	.L54
	call	xor128.part.0
	movl	%eax, %r9d
	movq	(%rsp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L55
	addq	$1, %r10
	cmpq	$1024, %r10
	jne	.L53
	leaq	8(%rsp), %r12
	movl	$50000000, %edx
	movl	$32, %esi
	xorl	%r13d, %r13d
	movq	%r12, %rdi
	call	makeArrayInt
	.p2align 4,,10
	.p2align 3
.L59:
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
.L58:
	movl	(%rsi,%rax,4), %ecx
	movq	(%r8,%rax,8), %rdx
	addq	$1, %rax
	movl	%ecx, (%rdx,%r13)
	cmpq	$32, %rax
	jne	.L58
	addq	$4, %r13
	cmpq	$200000000, %r13
	jne	.L59
	xorl	%r14d, %r14d
	leaq	16(%rsp), %r13
.L64:
	movq	(%r8,%r14,8), %r11
	movl	$32, %r10d
	xorl	%r9d, %r9d
	movl	$-2147483648, %esi
	leaq	200000000(%r11), %rdi
	.p2align 4,,10
	.p2align 3
.L60:
	movq	%r11, %rax
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L61:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L61
	leal	(%r9,%rsi), %eax
	cmpl	$25000000, %edx
	cmovg	%eax, %r9d
	shrl	%esi
	subl	$1, %r10d
	jne	.L60
	movl	%r9d, 0(%r13,%r14,4)
	addq	$1, %r14
	cmpq	$32, %r14
	jne	.L64
	leaq	144(%rsp), %r15
	leaq	.LC1(%rip), %r14
.L65:
	movl	0(%r13), %edx
	movq	%r14, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %r13
	call	__printf_chk@PLT
	cmpq	%r13, %r15
	jne	.L65
	movl	$32, %esi
	movq	%r12, %rdi
	call	freeArrayInt
	movl	$1024, %esi
	movq	%rbp, %rdi
	call	freeArrayInt
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	leaq	.LC4(%rip), %rsi
	subq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC2(%rip), %xmm0
	movl	$1, %eax
	mulsd	.LC3(%rip), %xmm0
	call	__printf_chk@PLT
	movq	152(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L74
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
.L74:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE59:
	.size	main, .-main
	.data
	.align 4
	.type	w.4613, @object
	.size	w.4613, 4
w.4613:
	.long	88675123
	.align 4
	.type	z.4612, @object
	.size	z.4612, 4
z.4612:
	.long	521288629
	.align 4
	.type	y.4611, @object
	.size	y.4611, 4
y.4611:
	.long	362436069
	.align 4
	.type	x.4610, @object
	.size	x.4610, 4
x.4610:
	.long	123456789
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1093567616
	.align 8
.LC3:
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
