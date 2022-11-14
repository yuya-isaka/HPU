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
	.file	"ohashi_random.c"
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
	@ args = 0, pretend = 0, frame = 1040
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subw	sp, sp, #1052
	ldr	r4, .L61+16
	ldr	r3, .L61+20
.LPIC1:
	add	r4, pc
	ldr	r5, [r4, r3]
	ldr	r3, [r5]
	str	r3, [sp, #1044]
	bl	clock(PLT)
	mov	r6, r0
	ldr	r0, .L61+24
.LPIC2:
	add	r0, pc
	bl	puts(PLT)
	ldr	r0, .L61+28
	movs	r1, #0
.LPIC3:
	add	r0, pc
	bl	open(PLT)
	adds	r1, r0, #1
	beq	.L27
	add	r8, sp, #20
	mov	r2, #1024
	mov	r7, r0
	mov	r1, r8
	bl	read(PLT)
	cmp	r0, #0
	blt	.L50
	ldr	r3, .L61+32
	mov	r0, r8
	ldr	r1, .L61+36
	ldr	r2, [r4, r3]
.LPIC5:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r7
	bl	close(PLT)
.L27:
	ldr	r0, .L61+40
	movs	r1, #0
.LPIC6:
	add	r0, pc
	bl	open(PLT)
	adds	r2, r0, #1
	mov	r7, r0
	beq	.L29
	add	r8, sp, #20
	mov	r2, #1024
	mov	r1, r8
	bl	read(PLT)
	cmp	r0, #0
	blt	.L51
	ldr	r3, .L61+44
	mov	r0, r8
	ldr	r1, .L61+48
	ldr	r2, [r4, r3]
.LPIC8:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r7
	bl	close(PLT)
.L29:
	ldr	r0, .L61+52
	movs	r1, #2
.LPIC9:
	add	r0, pc
	bl	open(PLT)
	subs	r8, r0, #0
	blt	.L52
	ldr	r0, .L61+56
	movs	r1, #2
.LPIC11:
	add	r0, pc
	bl	open(PLT)
	subs	r9, r0, #0
	blt	.L53
	ldr	r0, .L61+60
	movw	r1, #4098
	movt	r1, 16
.LPIC13:
	add	r0, pc
	bl	open(PLT)
	subs	r10, r0, #0
	blt	.L54
	ldr	r0, .L61+64
	movw	r1, #4098
	movt	r1, 16
.LPIC15:
	add	r0, pc
	bl	open(PLT)
	subs	fp, r0, #0
	blt	.L55
	movs	r7, #0
	movs	r3, #1
	strd	fp, r7, [sp]
	mov	r0, r7
	movs	r2, #3
	mov	r1, #4096
	bl	mmap(PLT)
	ldr	r3, .L61+68
	ldr	r3, [r4, r3]
	str	r3, [sp, #12]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L56
	movs	r3, #1
	str	r7, [sp, #4]
	str	r10, [sp]
	movs	r2, #3
	mov	r1, #4096
	mov	r0, r7
	bl	mmap(PLT)
	ldr	r3, .L61+72
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L57
	movs	r3, #1
	str	r7, [sp, #4]
	mov	r1, #25856
	str	r8, [sp]
	movt	r1, 7629
	movs	r2, #3
	mov	r0, r7
	bl	mmap(PLT)
	ldr	r3, .L61+76
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L58
	movs	r3, #1
	str	r7, [sp, #4]
	mov	r0, r7
	str	r9, [sp]
	mov	r1, #2304
	movs	r2, #3
	movt	r1, 61
	bl	mmap(PLT)
	ldr	r3, .L61+80
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L59
	ldr	r3, [sp, #12]
	movw	r1, #1023
	ldr	r2, [r3]
	movs	r3, #1
	str	r1, [r2, #4]
	str	r3, [r2]
.L40:
	ldr	r3, [r2]
	lsls	r3, r3, #31
	bmi	.L40
	ldr	r0, .L61+84
.LPIC21:
	add	r0, pc
	bl	puts(PLT)
	bl	clock(PLT)
	vldr.64	d4, .L61
	ldr	r1, .L61+88
	vldr.64	d6, .L61+8
.LPIC22:
	add	r1, pc
	subs	r6, r0, r6
	movs	r0, #1
	vmov	s15, r6	@ int
	vcvt.f64.s32	d7, s15
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	b	.L32
.L53:
	ldr	r0, .L61+92
.LPIC12:
	add	r0, pc
	bl	perror(PLT)
.L32:
	ldr	r2, [sp, #1044]
	movs	r0, #0
	ldr	r3, [r5]
	cmp	r2, r3
	bne	.L60
	addw	sp, sp, #1052
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L52:
	ldr	r0, .L61+96
.LPIC10:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L56:
	ldr	r0, .L61+100
.LPIC17:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, fp
	bl	close(PLT)
	b	.L32
.L54:
	ldr	r0, .L61+104
.LPIC14:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L55:
	ldr	r0, .L61+108
.LPIC16:
	add	r0, pc
	bl	perror(PLT)
	b	.L32
.L57:
	ldr	r0, .L61+112
.LPIC18:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r10
	bl	close(PLT)
	b	.L32
.L58:
	ldr	r0, .L61+116
.LPIC19:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r8
	bl	close(PLT)
	b	.L32
.L59:
	ldr	r0, .L61+120
.LPIC20:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r9
	bl	close(PLT)
	b	.L32
.L60:
	bl	__stack_chk_fail(PLT)
.L51:
	ldr	r0, .L61+124
.LPIC7:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L50:
	ldr	r0, .L61+128
.LPIC4:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L62:
	.align	3
.L61:
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
	.ascii	"\012  --------------------------------------- HDC P"
	.ascii	"rogram end -------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC20:
	.ascii	"\012\012  time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
