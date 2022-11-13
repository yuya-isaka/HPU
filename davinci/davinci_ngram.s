	.file	"davinci_ngram.c"
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
	.globl	shifter_1024
	.type	shifter_1024, @function
shifter_1024:
.LFB57:
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
	je	.L38
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
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L34:
	orl	%eax, -4(%rdi,%rdx,4)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	je	.L42
.L39:
	movq	%rax, %rdx
.L36:
	movl	(%r11,%rdx,4), %esi
	movl	%r10d, %ecx
	movl	%esi, %eax
	andl	%r9d, %eax
	sall	%cl, %eax
	movl	%ebp, %ecx
	shrl	%cl, %esi
	orl	%esi, (%rdi,%rdx,4)
	testq	%rdx, %rdx
	jne	.L34
	orl	%eax, (%r12)
	leaq	1(%rdx), %rax
	cmpq	%rdx, %r8
	jne	.L39
.L42:
	movq	(%rbx), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L37:
	movl	(%rdi,%rdx,4), %eax
	movl	%eax, (%rcx,%rdx,4)
	movq	%rdx, %rax
	addq	$1, %rdx
	cmpq	%rax, %r8
	jne	.L37
.L38:
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
.LFE57:
	.size	shifter_1024, .-shifter_1024
	.p2align 4
	.globl	bounding
	.type	bounding, @function
bounding:
.LFB58:
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
.L44:
	movq	%r11, %rax
	xorl	%edx, %edx
	testq	%r10, %r10
	je	.L46
	.p2align 4,,10
	.p2align 3
.L45:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L45
	movslq	%edx, %rdx
	leal	(%r9,%rsi), %eax
	cmpq	%rbx, %rdx
	cmova	%eax, %r9d
.L46:
	shrl	%esi
	subl	$1, %r8d
	jne	.L44
	movl	%r9d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE58:
	.size	bounding, .-bounding
	.section	.rodata.str1.1
.LC1:
	.string	"data/decorate/en"
.LC2:
	.string	"\n"
.LC3:
	.string	"data/decorate/fr"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"\n------------- %s\343\201\256\345\255\246\347\277\222 -------------\n\n"
	.section	.rodata.str1.1
.LC5:
	.string	"r"
.LC6:
	.string	"  Failed: open file"
.LC7:
	.string	"EOF: %d\n"
.LC8:
	.string	"  Failed: fread file"
.LC9:
	.string	"all_ngram: %d\n"
.LC10:
	.string	"even: %d\n"
.LC11:
	.string	"%u\n"
	.section	.rodata.str1.8
	.align 8
.LC12:
	.string	"---------------------------------------------------------\n"
	.section	.rodata.str1.1
.LC15:
	.string	"\n\n  time %lf[ms]\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB59:
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
	subq	$152, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	call	clock@PLT
	leaq	.LC2(%rip), %rdi
	movq	%rax, -168(%rbp)
	call	puts@PLT
	movl	$32, %edx
	movl	$27, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, -72(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	movl	$123456789, x.4610(%rip)
	movl	$362436069, y.4611(%rip)
	movl	$521288629, z.4612(%rip)
	movl	$88675123, w.4613(%rip)
	movq	%rax, -176(%rbp)
	call	makeArrayInt
	xorl	%r10d, %r10d
.L53:
	movl	%r10d, %r8d
	leaq	0(,%r10,8), %rdi
	xorl	%esi, %esi
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L54:
	movq	-112(%rbp), %rax
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
	movq	-112(%rbp), %rax
	movq	(%rax,%rdi), %rax
	movl	%r9d, (%rax,%rsi,4)
	cmpl	$31, %esi
	jne	.L55
	addq	$1, %r10
	cmpq	$27, %r10
	jne	.L53
	leaq	-80(%rbp), %rax
	leaq	.LC1(%rip), %r12
	movl	$0, -140(%rbp)
	movq	%rax, -128(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, -160(%rbp)
.L56:
	movq	%r12, %rdx
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%r12, %rdi
	leaq	.LC5(%rip), %rsi
	call	fopen@PLT
	movq	%rax, %r12
	testq	%rax, %rax
	je	.L124
	xorl	%r13d, %r13d
	jmp	.L58
.L59:
	addl	$1, %r13d
.L58:
	movq	%r12, %rdi
	call	fgetc@PLT
	cmpl	$-1, %eax
	jne	.L59
	movl	$-1, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	movslq	%r13d, %r13
	leaq	.LC7(%rip), %rsi
	call	__printf_chk@PLT
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r12, %rdi
	call	fseek@PLT
	movl	$1, %esi
	movq	%r13, %rdi
	call	calloc@PLT
	movq	%r12, %rcx
	movq	%r13, %rdx
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	fread@PLT
	cmpq	%rax, %r13
	ja	.L125
	movq	%r12, %rdi
	call	fclose@PLT
	movq	%rbx, %rdx
.L61:
	movl	(%rdx), %ecx
	addq	$4, %rdx
	leal	-16843009(%rcx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	.L61
	movl	%eax, %ecx
	leaq	.LC9(%rip), %rsi
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	cmove	%rcx, %rdx
	movl	%eax, %edi
	addb	%al, %dil
	movl	-140(%rbp), %eax
	movl	$1, %edi
	sbbq	$3, %rdx
	subq	%rbx, %rdx
	leal	-2(%rax,%rdx), %r12d
	movl	%r12d, %r13d
	movl	%r12d, %edx
	andl	$1, %r13d
	movl	%r13d, %eax
	xorl	$1, %eax
	movl	%eax, -140(%rbp)
	movl	%eax, %r14d
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	%r14d, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	leaq	.LC10(%rip), %rsi
	call	__printf_chk@PLT
	leaq	-104(%rbp), %rax
	movl	$3, %edx
	movl	%r12d, %esi
	movq	%rax, %rdi
	movq	%rax, -184(%rbp)
	call	makeArray
	testl	%r12d, %r12d
	jle	.L65
	leal	-1(%r12), %edi
	movq	-104(%rbp), %r8
	xorl	%ecx, %ecx
	movq	%rdi, %r15
.L67:
	movq	(%r8,%rcx,8), %rsi
	xorl	%eax, %eax
.L66:
	movzbl	(%rbx,%rax), %edx
	subl	$97, %edx
	movw	%dx, (%rsi,%rax,2)
	addq	$1, %rax
	cmpq	$3, %rax
	jne	.L66
	leaq	1(%rcx), %rax
	addq	$1, %rbx
	cmpq	%rcx, %rdi
	je	.L126
	movq	%rax, %rcx
	jmp	.L67
.L126:
	leaq	-96(%rbp), %r14
	movl	%r12d, %edx
	movl	$32, %esi
	movq	%r14, %rdi
	call	makeArrayInt
	testl	%r13d, %r13d
	je	.L91
	movl	%r12d, -120(%rbp)
.L69:
	leaq	-88(%rbp), %rax
	movl	%r12d, -152(%rbp)
	xorl	%ebx, %ebx
	movq	%rax, -136(%rbp)
.L78:
	movq	-136(%rbp), %rdi
	movl	$32, %edx
	movl	$3, %esi
	leaq	0(,%rbx,8), %r15
	xorl	%r12d, %r12d
	call	makeArrayInt
.L71:
	movq	-104(%rbp), %rax
	movl	%r12d, %ecx
	movq	(%rax,%r15), %rax
	movzwl	(%rax,%r12,2), %edx
	movq	-112(%rbp), %rax
	leaq	(%rax,%rdx,8), %rsi
	movq	-88(%rbp), %rax
	movl	$32, %edx
	leaq	(%rax,%r12,8), %rdi
	addq	$1, %r12
	call	shifter_1024
	cmpq	$3, %r12
	jne	.L71
	movq	%rsp, %r8
	cmpq	%r8, %rsp
	je	.L73
.L127:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%r8, %rsp
	jne	.L127
.L73:
	addq	$-128, %rsp
	orq	$0, 120(%rsp)
	movq	%rsp, %r15
	movq	%r15, %rax
	leaq	128(%r15), %rdx
	.p2align 4,,10
	.p2align 3
.L75:
	movl	$0, (%rax)
	addq	$4, %rax
	cmpq	%rdx, %rax
	jne	.L75
	movq	-88(%rbp), %rax
	movq	(%rax), %rdi
	movq	8(%rax), %rsi
	movq	16(%rax), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L76:
	movl	(%rsi,%rax), %edx
	xorl	(%rdi,%rax), %edx
	xorl	(%r15,%rax), %edx
	xorl	(%rcx,%rax), %edx
	movl	%edx, (%r15,%rax)
	addq	$4, %rax
	cmpq	$128, %rax
	jne	.L76
	movq	-136(%rbp), %rdi
	movl	$3, %esi
	movq	%r8, -192(%rbp)
	call	freeArrayInt
	movq	-96(%rbp), %rdi
	movq	-192(%rbp), %r8
	xorl	%eax, %eax
	leaq	0(,%rbx,4), %rsi
	.p2align 4,,10
	.p2align 3
.L77:
	movq	(%rdi,%rax,8), %rdx
	movl	(%r15,%rax,4), %ecx
	addq	$1, %rax
	movl	%ecx, (%rdx,%rsi)
	cmpq	$32, %rax
	jne	.L77
	addq	$1, %rbx
	movq	%r8, %rsp
	cmpl	%ebx, -120(%rbp)
	jg	.L78
	movl	-152(%rbp), %r12d
	testl	%r13d, %r13d
	je	.L79
.L123:
	movslq	%r12d, %r10
.L84:
	movq	%rsp, -152(%rbp)
	cmpq	-152(%rbp), %rsp
	je	.L81
.L128:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	-152(%rbp), %rsp
	jne	.L128
.L81:
	addq	$-128, %rsp
	orq	$0, 120(%rsp)
	xorl	%r15d, %r15d
	movq	-96(%rbp), %rax
	movq	%rax, -120(%rbp)
	leaq	0(,%r10,4), %rax
	movq	%r10, %rbx
	movq	%rsp, %r13
	movq	%rax, -136(%rbp)
	shrq	%rbx
.L83:
	movq	-120(%rbp), %rax
	movl	$32, %r8d
	xorl	%r9d, %r9d
	movl	$-2147483648, %esi
	movq	(%rax,%r15,8), %r11
	movq	-136(%rbp), %rax
	leaq	(%r11,%rax), %rdi
	.p2align 4,,10
	.p2align 3
.L85:
	movq	%r11, %rax
	xorl	%edx, %edx
	testq	%r10, %r10
	je	.L87
	.p2align 4,,10
	.p2align 3
.L86:
	xorl	%ecx, %ecx
	testl	%esi, (%rax)
	setne	%cl
	addq	$4, %rax
	addl	%ecx, %edx
	cmpq	%rax, %rdi
	jne	.L86
	movslq	%edx, %rdx
	leal	(%r9,%rsi), %eax
	cmpq	%rbx, %rdx
	cmova	%eax, %r9d
.L87:
	shrl	%esi
	subl	$1, %r8d
	jne	.L85
	movl	%r9d, 0(%r13,%r15,4)
	addq	$1, %r15
	cmpq	$32, %r15
	jne	.L83
	leaq	128(%r13), %rbx
.L89:
	movl	0(%r13), %edx
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %r13
	leaq	.LC11(%rip), %rsi
	call	__printf_chk@PLT
	cmpq	%rbx, %r13
	jne	.L89
	movl	$32, %esi
	movq	%r14, %rdi
	call	freeArrayInt
	movq	-184(%rbp), %rdi
	movl	%r12d, %esi
	call	freeArray
	addq	$8, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	-152(%rbp), %rsp
	cmpq	%rax, -160(%rbp)
	je	.L90
	movq	(%rax), %r12
	jmp	.L56
.L65:
	leaq	-96(%rbp), %r14
	movl	%r12d, %edx
	movl	$32, %esi
	movq	%r14, %rdi
	leal	-1(%r12), %r15d
	call	makeArrayInt
	testl	%r13d, %r13d
	jne	.L123
.L91:
	movl	%r15d, -120(%rbp)
	testl	%r15d, %r15d
	jg	.L69
.L79:
	movq	-112(%rbp), %rax
	movslq	%r12d, %r10
	movq	-96(%rbp), %rcx
	leaq	-4(,%r10,4), %rdx
	movq	208(%rax), %rsi
	xorl	%eax, %eax
.L70:
	movl	(%rsi,%rax,4), %r8d
	movq	(%rcx,%rax,8), %rdi
	addq	$1, %rax
	movl	%r8d, (%rdi,%rdx)
	cmpq	$32, %rax
	jne	.L70
	jmp	.L84
.L90:
	movq	-176(%rbp), %rdi
	movl	$27, %esi
	call	freeArrayInt
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	subq	-168(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC13(%rip), %xmm0
	movl	$1, %eax
	leaq	.LC15(%rip), %rsi
	mulsd	.LC14(%rip), %xmm0
	call	__printf_chk@PLT
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L129
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
.L124:
	.cfi_restore_state
	leaq	.LC6(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L129:
	call	__stack_chk_fail@PLT
.L125:
	leaq	.LC8(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
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
.LC13:
	.long	0
	.long	1093567616
	.align 8
.LC14:
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
