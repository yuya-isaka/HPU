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
	.file	"bind_bound.c"
	.text
	.align	1
	.p2align 2,,3
	.global	makeArrayInt
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	makeArrayInt, %function
makeArrayInt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r1
	mov	r4, r0
	movs	r1, #4
	mov	r0, r5
	mov	r6, r2
	bl	calloc(PLT)
	cmp	r5, #0
	str	r0, [r4]
	ble	.L1
	add	r5, r0, r5, lsl #2
	mov	r4, r0
.L3:
	movs	r1, #4
	mov	r0, r6
	bl	calloc(PLT)
	str	r0, [r4], #4
	cmp	r5, r4
	bne	.L3
.L1:
	pop	{r4, r5, r6, pc}
	.size	makeArrayInt, .-makeArrayInt
	.align	1
	.p2align 2,,3
	.global	freeArrayInt
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	freeArrayInt, %function
freeArrayInt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r6, r1, #0
	mov	r5, r0
	ble	.L8
	movs	r4, #0
.L9:
	ldr	r3, [r5]
	ldr	r0, [r3, r4, lsl #2]
	adds	r4, r4, #1
	bl	free(PLT)
	cmp	r6, r4
	bne	.L9
.L8:
	ldr	r0, [r5]
	pop	{r4, r5, r6, lr}
	b	free(PLT)
	.size	freeArrayInt, .-freeArrayInt
	.align	1
	.p2align 2,,3
	.global	xor128
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	xor128, %function
xor128:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cbnz	r0, .L18
	ldr	r3, .L19
	push	{r4, r5}
.LPIC12:
	add	r3, pc
	ldr	r1, [r3, #12]
	ldr	r2, [r3]
	ldrd	r5, r4, [r3, #4]
	eor	r0, r1, r1, lsr #19
	str	r1, [r3, #8]
	eor	r2, r2, r2, lsl #11
	eors	r0, r0, r2
	strd	r5, r4, [r3]
	eor	r0, r0, r2, lsr #8
	str	r0, [r3, #12]
	pop	{r4, r5}
	bx	lr
.L18:
	ldr	r3, .L19+4
	movw	r0, #52501
	movw	r2, #21989
	movt	r0, 1883
.LPIC8:
	add	r3, pc
	movt	r2, 5530
	movw	r1, #15285
	movt	r1, 7954
	str	r0, [r3]
	movs	r0, #0
	str	r2, [r3, #4]
	movw	r2, #4915
	str	r1, [r3, #8]
	movt	r2, 1353
	str	r2, [r3, #12]
	bx	lr
.L20:
	.align	2
.L19:
	.word	.LANCHOR0-(.LPIC12+4)
	.word	.LANCHOR0-(.LPIC8+4)
	.size	xor128, .-xor128
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
	@ args = 0, pretend = 0, frame = 4248
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L50+16
	ldr	r2, .L50+20
.LPIC20:
	add	r3, pc
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #4224
	ldr	r3, [r3, r2]
	sub	sp, sp, #28
	add	r2, sp, #4224
	add	r8, sp, #24
	adds	r2, r2, #20
	sub	r6, r8, #8
	str	r3, [sp, #12]
	movw	r4, #4915
	ldr	r3, [r3]
	movt	r4, 1353
	mov	r10, #0
	mov	r7, r4
	str	r3, [r2]
	bl	clock(PLT)
	str	r0, [sp, #4]
	movs	r0, #10
	bl	srand(PLT)
	ldr	r3, .L50+24
	movw	r1, #52501
	mov	r0, r6
.LPIC21:
	add	r3, pc
	movt	r1, 1883
	movs	r2, #32
	str	r1, [r3]
	movw	r1, #21989
	movt	r1, 5530
	str	r1, [r3, #4]
	movw	r1, #15285
	movt	r1, 7954
	str	r1, [r3, #8]
	mov	r1, #1024
	str	r4, [r3, #12]
	bl	makeArrayInt(PLT)
.L22:
	lsl	r9, r10, #2
	movs	r4, #0
.L26:
	orr	r3, r4, r10
	lsls	r5, r4, #2
	adds	r4, r4, #1
	cbnz	r3, .L48
.L23:
	ldr	r3, [r6]
	ldr	r3, [r3, r9]
	str	r7, [r3, r5]
	orr	r3, r4, r10
	lsls	r5, r4, #2
	adds	r4, r4, #1
	cmp	r3, #0
	beq	.L23
.L48:
	movs	r0, #0
	bl	xor128(PLT)
	ldr	r3, [r6]
	cmp	r4, #32
	ldr	r3, [r3, r9]
	str	r0, [r3, r5]
	bne	.L26
	add	r10, r10, #1
	cmp	r10, #1024
	bne	.L22
	add	r3, sp, #148
	add	r0, sp, #4224
	sub	fp, r3, #4
	adds	r0, r0, #16
	movs	r1, #0
	mov	r2, fp
.L27:
	str	r1, [r2, #4]!
	cmp	r2, r0
	bne	.L27
	add	r9, r3, #4192
	movw	r10, #61568
	add	r9, r9, #28
	movt	r10, 762
	adds	r3, r3, #124
	str	r3, [sp, #8]
.L31:
	bl	rand(PLT)
	mov	r4, r0
	bl	rand(PLT)
	rsbs	r3, r4, #0
	ubfx	r4, r4, #0, #10
	ubfx	r3, r3, #0, #10
	ldr	r1, [r6]
	it	pl
	rsbpl	r4, r3, #0
	ldr	r5, [sp, #8]
	rsbs	r3, r0, #0
	ubfx	r2, r0, #0, #10
	ubfx	r3, r3, #0, #10
	ldr	r0, [r1, r4, lsl #2]
	it	pl
	rsbpl	r2, r3, #0
	sub	ip, r0, #4
	ldr	r7, [r1, r2, lsl #2]
	subs	r7, r7, #4
.L30:
	ldr	r4, [ip, #4]!
	sub	r1, r5, #128
	ldr	r3, [r7, #4]!
	movs	r0, #1
	eors	r4, r4, r3
.L29:
	tst	r4, r0
	ldr	r3, [r1, #4]!
	lsl	r0, r0, #1
	ite	ne
	movne	r2, #-1
	moveq	r2, #1
	cmp	r1, r5
	add	r3, r3, r2
	str	r3, [r1]
	bne	.L29
	add	r5, r1, #128
	cmp	r5, r9
	bne	.L30
	subs	r10, r10, #1
	bne	.L31
	sub	r4, r8, #8
	add	r8, r8, #120
	mov	r3, r10
	mov	ip, r4
.L32:
	str	r3, [ip, #4]!
	cmp	r8, ip
	bne	.L32
	mov	r5, r4
.L33:
	ldr	r1, [r5, #4]!
	mov	r0, fp
	movs	r2, #0
.L34:
	ldr	r3, [r0, #4]!
	lsrs	r3, r3, #31
	lsls	r3, r3, r2
	adds	r2, r2, #1
	cmp	r2, #32
	add	r1, r1, r3
	bne	.L34
	cmp	ip, r5
	str	r1, [r5]
	add	fp, fp, #128
	bne	.L33
	ldr	r8, .L50+28
.LPIC25:
	add	r8, pc
.L35:
	ldr	r2, [r4, #4]!
	mov	r1, r8
	movs	r0, #1
	bl	__printf_chk(PLT)
	cmp	r4, r5
	bne	.L35
	mov	r1, #1024
	mov	r0, r6
	bl	freeArrayInt(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #4]
	vldr.64	d4, .L50
	ldr	r1, .L50+32
	vldr.64	d6, .L50+8
.LPIC26:
	add	r1, pc
	subs	r7, r0, r3
	movs	r0, #1
	vmov	s15, r7	@ int
	vcvt.f64.s32	d7, s15
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	add	r3, sp, #4224
	adds	r3, r3, #20
	movs	r0, #0
	ldr	r2, [r3]
	ldr	r3, [sp, #12]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L49
	add	sp, sp, #4224
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L49:
	bl	__stack_chk_fail(PLT)
.L51:
	.align	3
.L50:
	.word	0
	.word	1093567616
	.word	0
	.word	1083129856
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC20+4)
	.word	__stack_chk_guard(GOT)
	.word	.LANCHOR0-(.LPIC21+4)
	.word	.LC0-(.LPIC25+4)
	.word	.LC1-(.LPIC26+4)
	.size	main, .-main
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	x.8164, %object
	.size	x.8164, 4
x.8164:
	.word	123456789
	.type	y.8165, %object
	.size	y.8165, 4
y.8165:
	.word	362436069
	.type	z.8166, %object
	.size	z.8166, 4
z.8166:
	.word	521288629
	.type	w.8167, %object
	.size	w.8167, 4
w.8167:
	.word	88675123
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%u\012\000"
.LC1:
	.ascii	"\012\012  time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
