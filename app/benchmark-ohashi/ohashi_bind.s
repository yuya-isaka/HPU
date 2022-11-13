	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"ohashi_bind.c"
	.text
	.align	1
	.p2align 2,,3
	.global	assemble
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	assemble, %function
assemble:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cbz	r0, .L2
	cmp	r1, #1
	beq	.L19
	cmp	r1, #2
	beq	.L20
	cmp	r1, #4
	beq	.L21
	cmp	r1, #6
	beq	.L22
	cmp	r1, #12
	bne	.L8
	orr	r0, r2, #33792
	bx	lr
.L2:
	cmp	r1, #3
	beq	.L9
	cmp	r1, #5
	beq	.L10
	cmp	r1, #7
	beq	.L11
	cmp	r1, #8
	beq	.L12
	cmp	r1, #9
	beq	.L13
	cmp	r1, #10
	beq	.L14
	cmp	r1, #11
	beq	.L23
.L8:
	ldr	r1, .L24
	movs	r0, #1
	push	{r3, lr}
.LPIC0:
	add	r1, pc
	bl	__printf_chk(PLT)
	movs	r0, #0
	pop	{r3, pc}
.L19:
	orr	r0, r2, #49152
	bx	lr
.L9:
	mov	r0, #16384
	bx	lr
.L21:
	orr	r0, r2, #36864
	bx	lr
.L20:
	orr	r0, r2, #40960
	bx	lr
.L10:
	mov	r0, #8192
	bx	lr
.L11:
	mov	r0, #4096
	bx	lr
.L22:
	orr	r0, r2, #34816
	bx	lr
.L12:
	mov	r0, #2048
	bx	lr
.L13:
	mov	r0, #1024
	bx	lr
.L23:
	mov	r0, #256
	bx	lr
.L14:
	mov	r0, #512
	bx	lr
.L25:
	.align	2
.L24:
	.word	.LC0-(.LPIC0+4)
	.size	assemble, .-assemble
	.section	.text.startup,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 1064
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subw	sp, sp, #1076
	ldr	r4, .L88+16
	ldr	r3, .L88+20
.LPIC1:
	add	r4, pc
	ldr	r3, [r4, r3]
	str	r3, [sp, #12]
	ldr	r3, [r3]
	str	r3, [sp, #1068]
	bl	clock(PLT)
	str	r0, [sp, #16]
	ldr	r0, .L88+24
.LPIC2:
	add	r0, pc
	bl	puts(PLT)
	ldr	r0, .L88+28
	movs	r1, #0
.LPIC3:
	add	r0, pc
	bl	open(PLT)
	adds	r7, r0, #1
	beq	.L27
	add	r7, sp, #44
	mov	r2, #1024
	mov	r5, r0
	mov	r1, r7
	bl	read(PLT)
	cmp	r0, #0
	blt	.L75
	ldr	r3, .L88+32
	mov	r0, r7
	ldr	r1, .L88+36
	ldr	r10, [r4, r3]
.LPIC5:
	add	r1, pc
	mov	r2, r10
	bl	__isoc99_sscanf(PLT)
	mov	r0, r5
	bl	close(PLT)
.L27:
	ldr	r0, .L88+40
	movs	r1, #0
.LPIC6:
	add	r0, pc
	bl	open(PLT)
	adds	r6, r0, #1
	mov	r5, r0
	beq	.L29
	add	r7, sp, #44
	mov	r2, #1024
	mov	r1, r7
	bl	read(PLT)
	cmp	r0, #0
	blt	.L76
	ldr	r3, .L88+44
	mov	r0, r7
	ldr	r1, .L88+48
	ldr	r9, [r4, r3]
.LPIC8:
	add	r1, pc
	mov	r2, r9
	bl	__isoc99_sscanf(PLT)
	mov	r0, r5
	bl	close(PLT)
.L29:
	ldr	r0, .L88+52
	movs	r1, #2
.LPIC9:
	add	r0, pc
	bl	open(PLT)
	subs	r8, r0, #0
	blt	.L77
	ldr	r0, .L88+56
	movs	r1, #2
.LPIC11:
	add	r0, pc
	bl	open(PLT)
	subs	r6, r0, #0
	blt	.L78
	ldr	r0, .L88+60
	movw	r1, #4098
	movt	r1, 16
.LPIC13:
	add	r0, pc
	bl	open(PLT)
	subs	r7, r0, #0
	blt	.L79
	ldr	r0, .L88+64
	movw	r1, #4098
	movt	r1, 16
.LPIC15:
	add	r0, pc
	bl	open(PLT)
	subs	r10, r0, #0
	blt	.L80
	movs	r5, #0
	movs	r3, #1
	strd	r10, r5, [sp]
	mov	r0, r5
	movs	r2, #3
	mov	r1, #4096
	bl	mmap(PLT)
	ldr	r3, .L88+68
	ldr	r3, [r4, r3]
	str	r3, [sp, #20]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L81
	movs	r3, #1
	str	r5, [sp, #4]
	str	r7, [sp]
	movs	r2, #3
	mov	r1, #4096
	mov	r0, r5
	bl	mmap(PLT)
	ldr	r3, .L88+72
	ldr	r3, [r4, r3]
	str	r3, [sp, #24]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L82
	movs	r3, #1
	str	r5, [sp, #4]
	mov	r1, #25856
	str	r8, [sp]
	movt	r1, 7629
	movs	r2, #3
	mov	r0, r5
	bl	mmap(PLT)
	ldr	r3, .L88+76
	ldr	r7, [r4, r3]
	str	r0, [r7]
	adds	r0, r0, #1
	beq	.L83
	movs	r3, #1
	str	r5, [sp, #4]
	mov	r0, r5
	str	r6, [sp]
	mov	r1, #2304
	movs	r2, #3
	movt	r1, 61
	bl	mmap(PLT)
	ldr	r3, .L88+80
	ldr	r8, [r4, r3]
	str	r0, [r8]
	adds	r0, r0, #1
	beq	.L84
	ldr	r3, [sp, #24]
	ldr	r2, [r3]
	movs	r3, #4
	str	r3, [r2, #48]
	str	r3, [r2]
.L40:
	ldr	r3, [r2]
	ands	r3, r3, #4
	bne	.L40
	ldr	r2, [sp, #20]
	mov	r6, r3
	str	r3, [sp, #32]
	movs	r0, #10
	movw	r1, #44808
	movw	r5, #35391
	ldr	r3, [r2]
	movs	r2, #2
	movt	r1, 47
	movt	r5, 503
	str	r1, [sp, #28]
	str	r2, [r3]
	str	r5, [sp, #36]
	bl	srand(PLT)
	ldr	r1, .L88+32
	ldr	r2, .L88+44
	ldr	r10, [r4, r1]
	ldr	r9, [r4, r2]
.L41:
	ldr	r3, [sp, #32]
	lsls	r5, r3, #1
	add	r4, r5, #32
	b	.L42
.L55:
	mov	r5, r3
.L42:
	bl	rand(PLT)
	ldr	r2, [r7]
	rsbs	r3, r0, #0
	ubfx	r0, r0, #0, #10
	ubfx	r3, r3, #0, #10
	it	pl
	rsbpl	r0, r3, #0
	adds	r3, r5, #2
	orr	r0, r0, #40960
	cmp	r4, r3
	uxth	r0, r0
	strh	r0, [r2, r5]	@ movhi
	bne	.L55
	add	fp, r5, #98
	add	r4, r4, r2
	add	r2, r2, fp
.L43:
	strh	r6, [r4], #2	@ movhi
	cmp	r2, r4
	bne	.L43
	add	r4, r5, #130
.L44:
	bl	rand(PLT)
	ldr	r2, [r7]
	rsbs	r3, r0, #0
	ubfx	r0, r0, #0, #10
	ubfx	r3, r3, #0, #10
	it	pl
	rsbpl	r0, r3, #0
	orr	r0, r0, #34816
	uxth	r0, r0
	strh	r0, [r2, fp]	@ movhi
	add	fp, fp, #2
	cmp	fp, r4
	bne	.L44
	add	r1, r5, #226
	add	r3, r2, fp
	add	r1, r1, r2
.L45:
	strh	r6, [r3], #2	@ movhi
	cmp	r3, r1
	bne	.L45
	ldr	r1, [sp, #32]
	add	r0, r1, #128
	ldr	r1, [sp, #36]
	cmp	r0, r1
	bgt	.L85
.L46:
	ldr	r3, [sp, #28]
	subs	r3, r3, #1
	str	r3, [sp, #28]
	bne	.L86
	lsls	r4, r0, #1
	add	r1, r2, #128
	adds	r3, r4, #2
	add	r4, r4, r1
	ldr	r1, [sp, #28]
	add	r3, r3, r2
	mov	r5, #1024
	strh	r5, [r2, r0, lsl #1]	@ movhi
.L51:
	strh	r1, [r3], #2	@ movhi
	cmp	r4, r3
	bne	.L51
	ldr	r3, [sp, #24]
	add	r2, r0, #64
	ldr	r5, [r10]
	movs	r1, #1
	ldr	r4, [r9]
	lsls	r2, r2, r1
	ldr	r3, [r3]
	movs	r0, #128
	str	r1, [r3]
	str	r5, [r3, #24]
	str	r2, [r3, #40]
	str	r1, [r3, #48]
	str	r4, [r3, #72]
	str	r0, [r3, #88]
.L52:
	ldr	r2, [r3, #52]
	lsls	r2, r2, #19
	bpl	.L52
	ldr	r5, .L88+84
	movs	r4, #0
.LPIC21:
	add	r5, pc
.L53:
	ldr	r3, [r8]
	mov	r1, r5
	movs	r0, #1
	ldr	r2, [r3, r4]
	adds	r4, r4, #4
	bl	__printf_chk(PLT)
	cmp	r4, #128
	bne	.L53
	ldr	r3, [sp, #20]
	movs	r2, #0
	ldr	r0, .L88+88
	ldr	r3, [r3]
.LPIC22:
	add	r0, pc
	str	r2, [r3]
	bl	puts(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #16]
	vldr.64	d4, .L88
	ldr	r1, .L88+92
	vldr.64	d6, .L88+8
.LPIC23:
	add	r1, pc
	sub	fp, r0, r3
	movs	r0, #1
	vmov	s15, fp	@ int
	vcvt.f64.s32	d7, s15
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	b	.L32
.L78:
	ldr	r0, .L88+96
.LPIC12:
	add	r0, pc
	bl	perror(PLT)
.L32:
	ldr	r3, [sp, #12]
	movs	r0, #0
	ldr	r2, [sp, #1068]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L87
	addw	sp, sp, #1076
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L77:
	ldr	r0, .L88+100
.LPIC10:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L81:
	ldr	r0, .L88+104
.LPIC17:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r10
	bl	close(PLT)
	b	.L32
.L79:
	ldr	r0, .L88+108
.LPIC14:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L80:
	ldr	r0, .L88+112
.LPIC16:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L85:
	add	r1, r5, #228
	add	r0, r5, #354
	add	r1, r1, r2
	add	r0, r0, r2
	mov	r4, #1024	@ movhi
	strh	r4, [r3]	@ movhi
.L47:
	strh	r6, [r1], #2	@ movhi
	cmp	r0, r1
	bne	.L47
	ldr	r3, [sp, #24]
	movs	r0, #1
	ldr	r4, [r10]
	ldr	r5, [r9]
	ldr	r1, [r3]
	ldr	r3, [sp, #32]
	adds	r3, r3, #192
	str	r0, [r1]
	str	r4, [r1, #24]
	movs	r4, #128
	lsls	r3, r3, r0
	str	r3, [r1, #40]
	str	r0, [r1, #48]
	str	r5, [r1, #72]
	str	r4, [r1, #88]
.L48:
	ldr	r3, [r1, #52]
	lsls	r0, r3, #19
	bpl	.L48
	movs	r3, #4
	str	r3, [r1, #48]
	str	r3, [r1]
.L49:
	ldr	r0, [r1]
	ands	r0, r0, #4
	bne	.L49
	b	.L46
.L82:
	ldr	r0, .L88+116
.LPIC18:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r7
	bl	close(PLT)
	b	.L32
.L83:
	ldr	r0, .L88+120
.LPIC19:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r8
	bl	close(PLT)
	b	.L32
.L84:
	ldr	r0, .L88+124
.LPIC20:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r6
	bl	close(PLT)
	b	.L32
.L87:
	bl	__stack_chk_fail(PLT)
.L76:
	ldr	r0, .L88+128
.LPIC7:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L75:
	ldr	r0, .L88+132
.LPIC4:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L86:
	str	r0, [sp, #32]
	b	.L41
.L89:
	.align	3
.L88:
	.word	0
	.word	1093567616
	.word	0
	.word	1083129856
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC1+4)
	.word	__stack_chk_guard(GOT)
	.word	.LC1-(.LPIC2+4)
	.word	.LC2-(.LPIC3+4)
	.word	src_phys(GOT)
	.word	.LC4-(.LPIC5+4)
	.word	.LC5-(.LPIC6+4)
	.word	dst_phys(GOT)
	.word	.LC4-(.LPIC8+4)
	.word	.LC7-(.LPIC9+4)
	.word	.LC9-(.LPIC11+4)
	.word	.LC11-(.LPIC13+4)
	.word	.LC13-(.LPIC15+4)
	.word	top(GOT)
	.word	dma(GOT)
	.word	src(GOT)
	.word	dst(GOT)
	.word	.LC19-(.LPIC21+4)
	.word	.LC20-(.LPIC22+4)
	.word	.LC21-(.LPIC23+4)
	.word	.LC10-(.LPIC12+4)
	.word	.LC8-(.LPIC10+4)
	.word	.LC15-(.LPIC17+4)
	.word	.LC12-(.LPIC14+4)
	.word	.LC14-(.LPIC16+4)
	.word	.LC16-(.LPIC18+4)
	.word	.LC17-(.LPIC19+4)
	.word	.LC18-(.LPIC20+4)
	.word	.LC6-(.LPIC7+4)
	.word	.LC3-(.LPIC4+4)
	.size	main, .-main
	.comm	dst_phys,4,4
	.comm	src_phys,4,4
	.comm	dst,4,4
	.comm	src,4,4
	.comm	dma,4,4
	.comm	top,4,4
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"error\000"
	.space	2
.LC1:
	.ascii	"\012  -------------------------------------- HDC Pr"
	.ascii	"ogram start ------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC2:
	.ascii	"/sys/class/u-dma-buf/udmabuf0/phys_addr\000"
.LC3:
	.ascii	"  Failed: read /sys/class/u-dma-buf/udmabuf0/phys_a"
	.ascii	"ddr\000"
	.space	1
.LC4:
	.ascii	"%lx\000"
.LC5:
	.ascii	"/sys/class/u-dma-buf/udmabuf1/phys_addr\000"
.LC6:
	.ascii	"  Failed: read /sys/class/u-dma-buf/udmabuf1/phys_a"
	.ascii	"ddr\000"
	.space	1
.LC7:
	.ascii	"/dev/udmabuf0\000"
	.space	2
.LC8:
	.ascii	"  Failed: open /dev/udmabuf0\000"
	.space	3
.LC9:
	.ascii	"/dev/udmabuf1\000"
	.space	2
.LC10:
	.ascii	"  Failed: open /dev/udmabuf1\000"
	.space	3
.LC11:
	.ascii	"/dev/uio0\000"
	.space	2
.LC12:
	.ascii	"  Falied: open /dev/uio0\000"
	.space	3
.LC13:
	.ascii	"/dev/uio1\000"
	.space	2
.LC14:
	.ascii	"  Failed: open /dev/uio1\000"
	.space	3
.LC15:
	.ascii	"  mmap top\000"
	.space	1
.LC16:
	.ascii	"  mmap dma\000"
	.space	1
.LC17:
	.ascii	"  mmap src\000"
	.space	1
.LC18:
	.ascii	"  mmap dst\000"
	.space	1
.LC19:
	.ascii	"%u\012\000"
.LC20:
	.ascii	"\012  --------------------------------------- HDC P"
	.ascii	"rogram end -------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC21:
	.ascii	"\012\012  time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
