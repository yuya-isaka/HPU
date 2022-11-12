	.file	"addition.c"
	.text
	.section	.rodata
.LC0:
	.string	"leaks -q a.out"
	.text
	.type	destructor, @function
destructor:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rdi
	call	system@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	destructor, .-destructor
	.section	.fini_array,"aw"
	.align 8
	.quad	destructor
	.text
	.globl	makeArray
	.type	makeArray, @function
makeArray:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	-44(%rbp), %eax
	cltq
	movl	$8, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movl	$0, -20(%rbp)
	jmp	.L3
.L4:
	movl	-48(%rbp), %eax
	cltq
	movq	-40(%rbp), %rdx
	movq	(%rdx), %rdx
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	leaq	(%rdx,%rcx), %rbx
	movl	$2, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, (%rbx)
	addl	$1, -20(%rbp)
.L3:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L4
	nop
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	makeArray, .-makeArray
	.globl	freeArray
	.type	freeArray, @function
freeArray:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L7
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	freeArray, .-freeArray
	.globl	makeArrayInt
	.type	makeArrayInt, @function
makeArrayInt:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	-44(%rbp), %eax
	cltq
	movl	$8, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movl	$0, -20(%rbp)
	jmp	.L9
.L10:
	movl	-48(%rbp), %eax
	cltq
	movq	-40(%rbp), %rdx
	movq	(%rdx), %rdx
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	leaq	(%rdx,%rcx), %rbx
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, (%rbx)
	addl	$1, -20(%rbp)
.L9:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L10
	nop
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	makeArrayInt, .-makeArrayInt
	.globl	freeArrayInt
	.type	freeArrayInt, @function
freeArrayInt:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L12
.L13:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L13
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	freeArrayInt, .-freeArrayInt
	.globl	xor128
	.type	xor128, @function
xor128:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	cmpl	$0, -20(%rbp)
	je	.L15
	movl	$123456789, x.4235(%rip)
	movl	$362436069, y.4236(%rip)
	movl	$521288629, z.4237(%rip)
	movl	$88675123, w.4238(%rip)
	movl	$0, %eax
	jmp	.L16
.L15:
	movl	x.4235(%rip), %eax
	sall	$11, %eax
	movl	%eax, %edx
	movl	x.4235(%rip), %eax
	xorl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	y.4236(%rip), %eax
	movl	%eax, x.4235(%rip)
	movl	z.4237(%rip), %eax
	movl	%eax, y.4236(%rip)
	movl	w.4238(%rip), %eax
	movl	%eax, z.4237(%rip)
	movl	w.4238(%rip), %eax
	shrl	$19, %eax
	movl	%eax, %edx
	movl	w.4238(%rip), %eax
	xorl	%eax, %edx
	movl	-4(%rbp), %eax
	shrl	$8, %eax
	xorl	-4(%rbp), %eax
	xorl	%edx, %eax
	movl	%eax, w.4238(%rip)
	movl	w.4238(%rip), %eax
.L16:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	xor128, .-xor128
	.globl	shifter_32
	.type	shifter_32, @function
shifter_32:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %ecx
	shrl	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-28(%rbp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	andl	-4(%rbp), %eax
	movl	%eax, %edx
	movl	$32, %eax
	subl	-28(%rbp), %eax
	movl	%eax, %ecx
	sall	%cl, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	shifter_32, .-shifter_32
	.globl	grab_bit
	.type	grab_bit, @function
grab_bit:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -16(%rbp)
	movl	$-2147483648, -12(%rbp)
	jmp	.L20
.L24:
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L21
.L22:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	andl	-12(%rbp), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	addl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L21:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -32(%rbp)
	ja	.L22
	movl	-8(%rbp), %eax
	cltq
	movq	-32(%rbp), %rdx
	shrq	%rdx
	cmpq	%rdx, %rax
	jbe	.L23
	movl	-12(%rbp), %eax
	addl	%eax, -16(%rbp)
.L23:
	shrl	-12(%rbp)
.L20:
	cmpl	$0, -12(%rbp)
	jne	.L24
	movl	-16(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	grab_bit, .-grab_bit
	.globl	shifter_1024
	.type	shifter_1024, @function
shifter_1024:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movl	%ecx, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	-52(%rbp), %eax
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, -16(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L27
.L30:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -32(%rbp)
	movl	-56(%rbp), %edx
	leaq	-32(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	shifter_32
	movl	%eax, -20(%rbp)
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-16(%rbp), %rdx
	addq	%rcx, %rdx
	orl	-20(%rbp), %eax
	movl	%eax, (%rdx)
	cmpl	$0, -28(%rbp)
	jne	.L28
	movl	-52(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-32(%rbp), %edx
	movl	-52(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %eax
	leaq	0(,%rax,4), %rsi
	movq	-16(%rbp), %rax
	addq	%rsi, %rax
	orl	%ecx, %edx
	movl	%edx, (%rax)
	jmp	.L29
.L28:
	movl	-28(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rsi
	movq	-16(%rbp), %rax
	addq	%rsi, %rax
	orl	%ecx, %edx
	movl	%edx, (%rax)
.L29:
	addl	$1, -28(%rbp)
.L27:
	movl	-28(%rbp), %eax
	cmpl	%eax, -52(%rbp)
	ja	.L30
	movl	$0, -24(%rbp)
	jmp	.L31
.L32:
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	(%rcx), %eax
	movl	%eax, (%rdx)
	addl	$1, -24(%rbp)
.L31:
	movl	-24(%rbp), %eax
	cmpl	%eax, -52(%rbp)
	ja	.L32
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L33
	call	__stack_chk_fail@PLT
.L33:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	shifter_1024, .-shifter_1024
	.section	.rodata
.LC1:
	.string	"%u\n"
.LC4:
	.string	"\n\n  time %lf[ms]\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB15:
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
	subq	$136, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -164(%rbp)
	movq	%rsi, -176(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	call	clock@PLT
	movq	%rax, -96(%rbp)
	movl	$32, -128(%rbp)
	movl	$1024, -124(%rbp)
	movl	$50000000, -120(%rbp)
	movl	$10, %edi
	call	srand@PLT
	movl	$1, %edi
	call	xor128
	movl	-128(%rbp), %edx
	movl	-124(%rbp), %ecx
	leaq	-112(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	makeArrayInt
	movl	$0, -140(%rbp)
	jmp	.L35
.L40:
	movl	$0, -144(%rbp)
	jmp	.L36
.L39:
	movl	$0, -148(%rbp)
	cmpl	$0, -140(%rbp)
	jne	.L37
	cmpl	$0, -144(%rbp)
	jne	.L37
	movl	$88675123, -148(%rbp)
	jmp	.L38
.L37:
	movl	$0, %edi
	call	xor128
	movl	%eax, -148(%rbp)
.L38:
	movq	-112(%rbp), %rax
	movl	-140(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	-148(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -144(%rbp)
.L36:
	movl	-144(%rbp), %eax
	cmpl	-128(%rbp), %eax
	jl	.L39
	addl	$1, -140(%rbp)
.L35:
	movl	-140(%rbp), %eax
	cmpl	-124(%rbp), %eax
	jl	.L40
	movl	-120(%rbp), %edx
	movl	-128(%rbp), %ecx
	leaq	-104(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	makeArrayInt
	movl	$0, -152(%rbp)
	jmp	.L41
.L44:
	call	rand@PLT
	cltd
	shrl	$22, %edx
	addl	%edx, %eax
	andl	$1023, %eax
	subl	%edx, %eax
	movl	%eax, -116(%rbp)
	movl	$0, -156(%rbp)
	jmp	.L42
.L43:
	movq	-112(%rbp), %rax
	movl	-116(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-156(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	-104(%rbp), %rdx
	movl	-156(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	movl	-152(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$2, %rcx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -156(%rbp)
.L42:
	movl	-156(%rbp), %eax
	cmpl	-128(%rbp), %eax
	jl	.L43
	addl	$1, -152(%rbp)
.L41:
	movl	-152(%rbp), %eax
	cmpl	-120(%rbp), %eax
	jl	.L44
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-128(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -88(%rbp)
	movl	-128(%rbp), %eax
	cltq
	movq	%rax, %r14
	movl	$0, %r15d
	movl	-128(%rbp), %eax
	cltq
	movq	%rax, %r12
	movl	$0, %r13d
	movl	-128(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	movq	%rax, %rdx
	andq	$-4096, %rdx
	movq	%rsp, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rdx
.L45:
	cmpq	%rdx, %rsp
	je	.L46
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L45
.L46:
	movq	%rax, %rdx
	andl	$4095, %edx
	subq	%rdx, %rsp
	movq	%rax, %rdx
	andl	$4095, %edx
	testq	%rdx, %rdx
	je	.L47
	andl	$4095, %eax
	subq	$8, %rax
	addq	%rsp, %rax
	orq	$0, (%rax)
.L47:
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -80(%rbp)
	movl	$0, -136(%rbp)
	jmp	.L48
.L49:
	movl	-120(%rbp), %eax
	movslq	%eax, %rdx
	movq	-104(%rbp), %rax
	movl	-136(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	grab_bit
	movq	-80(%rbp), %rdx
	movl	-136(%rbp), %ecx
	movslq	%ecx, %rcx
	movl	%eax, (%rdx,%rcx,4)
	addl	$1, -136(%rbp)
.L48:
	movl	-136(%rbp), %eax
	cmpl	-128(%rbp), %eax
	jl	.L49
	movl	$0, -132(%rbp)
	jmp	.L50
.L51:
	movq	-80(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -132(%rbp)
.L50:
	movl	-132(%rbp), %eax
	cmpl	-128(%rbp), %eax
	jl	.L51
	movl	-128(%rbp), %edx
	leaq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	freeArrayInt
	movl	-124(%rbp), %edx
	leaq	-112(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	freeArrayInt
	call	clock@PLT
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	subq	-96(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC2(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movsd	.LC3(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC4(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	%rbx, %rsp
	movq	-56(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L53
	call	__stack_chk_fail@PLT
.L53:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.data
	.align 4
	.type	x.4235, @object
	.size	x.4235, 4
x.4235:
	.long	123456789
	.align 4
	.type	y.4236, @object
	.size	y.4236, 4
y.4236:
	.long	362436069
	.align 4
	.type	z.4237, @object
	.size	z.4237, 4
z.4237:
	.long	521288629
	.align 4
	.type	w.4238, @object
	.size	w.4238, 4
w.4238:
	.long	88675123
	.section	.rodata
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
