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
	.file	"bind_and_bound.c"
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
	.align	1
	.p2align 2,,3
	.global	bounding
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	bounding, %function
bounding:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	lsr	lr, r1, #1
	mov	ip, r0
	add	r6, r0, r1, lsl #2
	movs	r7, #32
	mov	r5, #-2147483648
	movs	r0, #0
.L22:
	mov	r2, ip
	movs	r4, #0
	cbz	r1, .L24
.L23:
	ldr	r3, [r2], #4
	ands	r3, r3, r5
	cmp	r3, #0
	it	ne
	addne	r4, r4, #1
	cmp	r6, r2
	bne	.L23
	cmp	lr, r4
	it	cc
	addcc	r0, r0, r5
.L24:
	subs	r7, r7, #1
	lsr	r5, r5, #1
	bne	.L22
	pop	{r4, r5, r6, r7, pc}
	.size	bounding, .-bounding
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
	@ args = 0, pretend = 0, frame = 160
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L52+16
	ldr	r3, .L52+20
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
.LPIC20:
	add	r2, pc
	sub	sp, sp, #164
	movw	r4, #4915
	add	r5, sp, #20
	movt	r4, 1353
	str	r5, [sp, #12]
	mov	r8, #0
	ldr	r3, [r2, r3]
	mov	r6, r4
	str	r3, [sp, #8]
	ldr	r3, [r3]
	str	r3, [sp, #156]
	bl	clock(PLT)
	str	r0, [sp, #4]
	movs	r0, #10
	bl	srand(PLT)
	ldr	r3, .L52+24
	movw	r1, #52501
	mov	r0, r5
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
.L30:
	movs	r5, #0
	lsl	r7, r8, #2
	mov	r4, r5
	b	.L34
.L31:
	ldr	r3, [sp, #20]
	ldr	r3, [r3, r7]
	str	r6, [r3, r5]
.L32:
	adds	r5, r5, #4
.L34:
	orr	r3, r4, r8
	adds	r4, r4, #1
	cmp	r3, #0
	beq	.L31
	movs	r0, #0
	bl	xor128(PLT)
	ldr	r3, [sp, #20]
	cmp	r4, #32
	ldr	r3, [r3, r7]
	str	r0, [r3, r5]
	bne	.L32
	add	r8, r8, #1
	cmp	r8, #1024
	bne	.L30
	add	r3, sp, #24
	mov	r1, r4
	movw	r2, #61568
	movt	r2, 762
	mov	r0, r3
	mov	r9, r3
	bl	makeArrayInt(PLT)
	mov	r4, #49664
	movt	r4, 3051
	movs	r6, #0
.L36:
	bl	rand(PLT)
	mov	r5, r0
	bl	rand(PLT)
	rsbs	r3, r5, #0
	ubfx	r5, r5, #0, #10
	ubfx	r3, r3, #0, #10
	ldr	r7, [sp, #20]
	it	pl
	rsbpl	r5, r3, #0
	ldr	r3, [r7, r5, lsl #2]
	add	ip, r3, #124
	rsbs	r2, r0, #0
	ubfx	r1, r0, #0, #10
	ubfx	r2, r2, #0, #10
	ldr	r0, [sp, #24]
	it	pl
	rsbpl	r1, r2, #0
	subs	r2, r3, #4
	sub	fp, r0, #4
	ldr	r1, [r7, r1, lsl #2]
	mov	r0, fp
	subs	r1, r1, #4
.L35:
	ldr	r3, [r2, #4]!
	ldr	r5, [r0, #4]!
	ldr	r7, [r1, #4]!
	cmp	ip, r2
	eor	r3, r3, r7
	str	r3, [r5, r6]
	bne	.L35
	adds	r6, r6, #4
	cmp	r6, r4
	bne	.L36
	add	r3, sp, #152
	movw	r10, #30784
	movt	r10, 381
	mov	r6, r9
	mov	lr, r3
	mov	r8, r9
.L41:
	ldr	r7, [fp, #4]!
	movw	r4, #49660
	movt	r4, 3051
	movs	r5, #32
	add	r4, r4, r7
	subs	r7, r7, #4
	mov	ip, #0
	mov	r0, #-2147483648
.L37:
	mov	r2, r7
	movs	r1, #0
.L38:
	ldr	r3, [r2, #4]!
	ands	r3, r3, r0
	cmp	r3, #0
	it	ne
	addne	r1, r1, #1
	cmp	r4, r2
	bne	.L38
	cmp	r1, r10
	it	gt
	addgt	ip, ip, r0
	subs	r5, r5, #1
	lsr	r0, r0, #1
	bne	.L37
	str	ip, [r6, #4]!
	cmp	lr, r6
	bne	.L41
	ldr	r4, .L52+28
.LPIC25:
	add	r4, pc
.L42:
	ldr	r2, [r8, #4]!
	mov	r1, r4
	movs	r0, #1
	bl	__printf_chk(PLT)
	cmp	r6, r8
	bne	.L42
	mov	r0, r9
	movs	r1, #32
	bl	freeArrayInt(PLT)
	mov	r1, #1024
	ldr	r0, [sp, #12]
	bl	freeArrayInt(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #4]
	vldr.64	d4, .L52
	ldr	r1, .L52+32
	vldr.64	d6, .L52+8
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
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #156]
	movs	r0, #0
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L51
	add	sp, sp, #164
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L51:
	bl	__stack_chk_fail(PLT)
.L53:
	.align	3
.L52:
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
	.ascii	"\012\012Bind-Bound time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
