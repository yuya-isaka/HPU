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
	.file	"ohashi_bound.c"
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
	@ args = 0, pretend = 0, frame = 1072
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subw	sp, sp, #1084
	ldr	r4, .L96+16
	ldr	r3, .L96+20
.LPIC1:
	add	r4, pc
	ldr	r3, [r4, r3]
	str	r3, [sp, #12]
	ldr	r3, [r3]
	str	r3, [sp, #1076]
	bl	clock(PLT)
	str	r0, [sp, #16]
	ldr	r0, .L96+24
.LPIC2:
	add	r0, pc
	bl	puts(PLT)
	ldr	r0, .L96+28
	movs	r1, #0
.LPIC3:
	add	r0, pc
	bl	open(PLT)
	adds	r3, r0, #1
	beq	.L27
	add	r6, sp, #52
	mov	r2, #1024
	mov	r5, r0
	mov	r1, r6
	bl	read(PLT)
	cmp	r0, #0
	blt	.L85
	ldr	r3, .L96+32
	mov	r0, r6
	ldr	r1, .L96+36
	ldr	r3, [r4, r3]
.LPIC5:
	add	r1, pc
	mov	r2, r3
	bl	__isoc99_sscanf(PLT)
	mov	r0, r5
	bl	close(PLT)
.L27:
	ldr	r0, .L96+40
	movs	r1, #0
.LPIC6:
	add	r0, pc
	bl	open(PLT)
	adds	r7, r0, #1
	mov	r5, r0
	beq	.L29
	add	r6, sp, #52
	mov	r2, #1024
	mov	r1, r6
	bl	read(PLT)
	cmp	r0, #0
	blt	.L86
	ldr	r3, .L96+44
	mov	r0, r6
	ldr	r1, .L96+48
	ldr	r3, [r4, r3]
.LPIC8:
	add	r1, pc
	mov	r2, r3
	bl	__isoc99_sscanf(PLT)
	mov	r0, r5
	bl	close(PLT)
.L29:
	ldr	r0, .L96+52
	movs	r1, #2
.LPIC9:
	add	r0, pc
	bl	open(PLT)
	subs	r6, r0, #0
	blt	.L87
	ldr	r0, .L96+56
	movs	r1, #2
.LPIC11:
	add	r0, pc
	bl	open(PLT)
	subs	r7, r0, #0
	blt	.L88
	ldr	r0, .L96+60
	movw	r1, #4098
	movt	r1, 16
.LPIC13:
	add	r0, pc
	bl	open(PLT)
	subs	r5, r0, #0
	blt	.L89
	ldr	r0, .L96+64
	movw	r1, #4098
	movt	r1, 16
.LPIC15:
	add	r0, pc
	bl	open(PLT)
	subs	r9, r0, #0
	blt	.L90
	mov	r8, #0
	movs	r3, #1
	strd	r9, r8, [sp]
	mov	r0, r8
	movs	r2, #3
	mov	r1, #4096
	bl	mmap(PLT)
	ldr	r3, .L96+68
	ldr	r3, [r4, r3]
	str	r3, [sp, #40]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L91
	movs	r3, #1
	str	r8, [sp, #4]
	str	r5, [sp]
	movs	r2, #3
	mov	r1, #4096
	mov	r0, r8
	bl	mmap(PLT)
	ldr	r3, .L96+72
	ldr	r3, [r4, r3]
	str	r3, [sp, #24]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L92
	movs	r3, #1
	str	r8, [sp, #4]
	mov	r1, #25856
	str	r6, [sp]
	movt	r1, 7629
	movs	r2, #3
	mov	r0, r8
	bl	mmap(PLT)
	ldr	r3, .L96+76
	ldr	r5, [r4, r3]
	str	r0, [r5]
	adds	r0, r0, #1
	beq	.L93
	str	r8, [sp, #4]
	mov	r0, r8
	movs	r3, #1
	str	r7, [sp]
	mov	r1, #2304
	movs	r2, #3
	movt	r1, 61
	bl	mmap(PLT)
	ldr	r3, .L96+80
	ldr	r8, [r4, r3]
	str	r0, [r8]
	adds	r0, r0, #1
	beq	.L94
	ldr	r3, [sp, #40]
	movw	r1, #1023
	ldr	r2, [r3]
	movs	r3, #1
	str	r1, [r2, #4]
	str	r3, [r2]
.L40:
	ldr	r3, [r2]
	lsls	r6, r3, #31
	bmi	.L40
	ldr	r3, [sp, #24]
	ldr	r1, [r3]
	movs	r3, #4
	str	r3, [r1, #48]
	str	r3, [r1]
.L41:
	ldr	r3, [r1]
	ands	r3, r3, #4
	bne	.L41
	movs	r1, #2
	movs	r0, #10
	str	r1, [r2]
	mov	r10, r3
	bl	srand(PLT)
	ldr	r1, .L96+84
	movs	r2, #13
	movs	r0, #1
.LPIC21:
	add	r1, pc
	mov	r6, #49152
	bl	__printf_chk(PLT)
	ldr	r1, .L96+88
	movw	r2, #61205
	movs	r0, #1
.LPIC22:
	add	r1, pc
	movt	r2, 3
	bl	__printf_chk(PLT)
	ldr	r1, .L96+32
	ldr	r2, .L96+44
	movw	r3, #5378
	movt	r3, 1007
	mov	r9, #5376
	ldr	r1, [r4, r1]
	movt	r6, 65535
	movt	r9, 1007
	str	r1, [sp, #32]
	ldr	r2, [r4, r2]
	str	r3, [sp, #36]
	mov	r3, #5504
	movt	r3, 1007
	str	r8, [sp, #44]
	str	r2, [sp, #28]
	movs	r2, #13
	mov	fp, r3
	str	r2, [sp, #20]
.L42:
	movs	r4, #32
	movs	r7, #0
.L52:
	mov	r8, r7
.L43:
	bl	rand(PLT)
	ldr	r2, [r5]
	rsbs	r3, r0, #0
	ubfx	r0, r0, #0, #10
	ubfx	r3, r3, #0, #10
	it	pl
	rsbpl	r0, r3, #0
	orrs	r0, r0, r6
	uxth	r0, r0
	strh	r0, [r2, r8]	@ movhi
	add	r8, r8, #2
	cmp	r4, r8
	bne	.L43
	add	r1, r7, #128
	adds	r3, r2, r4
	adds	r0, r2, r1
.L44:
	strh	r10, [r3], #2	@ movhi
	cmp	r0, r3
	bne	.L44
	add	r3, r7, #160
	add	r1, r1, r2
	add	ip, r2, r3
	mov	r0, #2048
.L45:
	strh	r0, [r1], #2	@ movhi
	cmp	ip, r1
	bne	.L45
	add	r7, r7, #256
	add	r3, r3, r2
	adds	r1, r2, r7
.L46:
	strh	r10, [r3], #2	@ movhi
	cmp	r1, r3
	bne	.L46
	cmp	r7, r9
	add	r4, r4, #256
	bne	.L52
	ldr	r3, [sp, #36]
	add	r1, r2, fp
	mov	r0, #1024
	strh	r0, [r2, r9]	@ movhi
	adds	r3, r2, r3
.L48:
	strh	r10, [r3], #2	@ movhi
	cmp	r1, r3
	bne	.L48
	ldr	r1, [sp, #32]
	movs	r2, #1
	ldr	r3, [sp, #24]
	ldr	r0, [sp, #28]
	ldr	r4, [r1]
	movs	r1, #128
	ldr	r3, [r3]
	ldr	r0, [r0]
	str	r2, [r3]
	str	r4, [r3, #24]
	str	fp, [r3, #40]
	str	r2, [r3, #48]
	str	r0, [r3, #72]
	str	r1, [r3, #88]
.L49:
	ldr	r2, [r3, #52]
	lsls	r4, r2, #19
	bpl	.L49
	movs	r2, #4
	str	r2, [r3, #48]
	str	r2, [r3]
.L50:
	ldr	r2, [r3]
	lsls	r0, r2, #29
	bmi	.L50
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
	bne	.L42
	ldr	r1, .L96+92
	movw	r2, #35575
	movs	r0, #1
	movt	r2, 65532
.LPIC23:
	add	r1, pc
	ldr	r8, [sp, #44]
	bl	__printf_chk(PLT)
	ldr	r0, [r5]
	ldr	r1, [sp, #20]
	mov	r3, #1024
	add	r4, r0, #128
	mov	r2, r0
	strh	r3, [r2], #2	@ movhi
	mov	r3, r2
.L53:
	strh	r1, [r3], #2	@ movhi
	cmp	r4, r3
	bne	.L53
	ldr	r1, [sp, #24]
	movs	r7, #1
	ldr	r6, [sp, #28]
	ldr	r4, [r1]
	ldr	r1, [sp, #32]
	ldr	r6, [r6]
	ldr	r5, [r1]
	movs	r1, #128
	str	r7, [r4]
	str	r5, [r4, #24]
	str	r1, [r4, #40]
	str	r7, [r4, #48]
	str	r6, [r4, #72]
	str	r1, [r4, #88]
.L54:
	ldr	r1, [r4, #52]
	lsls	r1, r1, #19
	bpl	.L54
	movs	r1, #4
	str	r1, [r4, #48]
	str	r1, [r4]
.L55:
	ldr	r1, [r4]
	ands	r1, r1, #4
	bne	.L55
	mov	r7, #1024
	strh	r7, [r0]	@ movhi
.L56:
	strh	r1, [r2], #2	@ movhi
	cmp	r3, r2
	bne	.L56
	movs	r2, #1
	movs	r3, #128
	str	r2, [r4]
	str	r5, [r4, #24]
	str	r3, [r4, #40]
	str	r2, [r4, #48]
	str	r6, [r4, #72]
	str	r3, [r4, #88]
.L57:
	ldr	r3, [r4, #52]
	lsls	r3, r3, #19
	bpl	.L57
	ldr	r5, .L96+96
	movs	r4, #0
.LPIC24:
	add	r5, pc
.L58:
	ldr	r3, [r8]
	mov	r1, r5
	movs	r0, #1
	ldr	r2, [r3, r4]
	adds	r4, r4, #4
	bl	__printf_chk(PLT)
	cmp	r4, #128
	bne	.L58
	ldr	r3, [sp, #40]
	movs	r2, #0
	ldr	r0, .L96+100
	ldr	r3, [r3]
.LPIC25:
	add	r0, pc
	str	r2, [r3]
	bl	puts(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #16]
	vldr.64	d4, .L96
	ldr	r1, .L96+104
	vldr.64	d6, .L96+8
.LPIC26:
	add	r1, pc
	subs	r3, r0, r3
	movs	r0, #1
	vmov	s14, r3	@ int
	vcvt.f64.s32	d7, s14
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	b	.L32
.L88:
	ldr	r0, .L96+108
.LPIC12:
	add	r0, pc
	bl	perror(PLT)
.L32:
	ldr	r3, [sp, #12]
	movs	r0, #0
	ldr	r2, [sp, #1076]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L95
	addw	sp, sp, #1084
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L87:
	ldr	r0, .L96+112
.LPIC10:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L91:
	ldr	r0, .L96+116
.LPIC17:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r9
	bl	close(PLT)
	b	.L32
.L89:
	ldr	r0, .L96+120
.LPIC14:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L90:
	ldr	r0, .L96+124
.LPIC16:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L92:
	ldr	r0, .L96+128
.LPIC18:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r5
	bl	close(PLT)
	b	.L32
.L93:
	ldr	r0, .L96+132
.LPIC19:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r6
	bl	close(PLT)
	b	.L32
.L94:
	ldr	r0, .L96+136
.LPIC20:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r7
	bl	close(PLT)
	b	.L32
.L95:
	bl	__stack_chk_fail(PLT)
.L86:
	ldr	r0, .L96+140
.LPIC7:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L85:
	ldr	r0, .L96+144
.LPIC4:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L97:
	.align	3
.L96:
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
	.word	.LC22-(.LPIC24+4)
	.word	.LC23-(.LPIC25+4)
	.word	.LC24-(.LPIC26+4)
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
	.ascii	"trial: %d\012\000"
	.space	1
.LC20:
	.ascii	"repeat: %d\012\000"
.LC21:
	.ascii	"repeat_remainder: %d\012\000"
	.space	2
.LC22:
	.ascii	"%u\012\000"
.LC23:
	.ascii	"\012  --------------------------------------- HDC P"
	.ascii	"rogram end -------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC24:
	.ascii	"\012\012  time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
