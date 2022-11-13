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
	.file	"random.c"
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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L31+16
	ldr	r2, .L31+20
.LPIC20:
	add	r3, pc
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #12
	ldr	r8, [r3, r2]
	movw	r4, #4915
	mov	r9, sp
	movt	r4, 1353
	movs	r6, #0
	ldr	r3, [r8]
	mov	r7, r4
	str	r3, [sp, #4]
	bl	clock(PLT)
	ldr	r3, .L31+24
	movs	r2, #32
	mov	r1, #1024
.LPIC21:
	add	r3, pc
	str	r4, [r3, #12]
	movw	r4, #52501
	movt	r4, 1883
	str	r4, [r3]
	movw	r4, #21989
	movt	r4, 5530
	str	r4, [r3, #4]
	movw	r4, #15285
	movt	r4, 7954
	str	r4, [r3, #8]
	mov	r10, r0
	mov	r0, r9
	bl	makeArrayInt(PLT)
.L22:
	movs	r5, #0
	lsl	fp, r6, #2
	mov	r4, r5
	b	.L26
.L23:
	ldr	r3, [sp]
	ldr	r3, [r3, fp]
	str	r7, [r3, r5]
.L24:
	adds	r5, r5, #4
.L26:
	orr	r3, r6, r4
	adds	r4, r4, #1
	cmp	r3, #0
	beq	.L23
	movs	r0, #0
	bl	xor128(PLT)
	ldr	r3, [sp]
	cmp	r4, #32
	ldr	r3, [r3, fp]
	str	r0, [r3, r5]
	bne	.L24
	adds	r6, r6, #1
	cmp	r6, #1024
	bne	.L22
	mov	r1, r6
	mov	r0, r9
	bl	freeArrayInt(PLT)
	bl	clock(PLT)
	vldr.64	d4, .L31
	ldr	r1, .L31+28
	vldr.64	d6, .L31+8
.LPIC25:
	add	r1, pc
	sub	r7, r0, r10
	movs	r0, #1
	vmov	s15, r7	@ int
	vcvt.f64.s32	d7, s15
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	ldr	r2, [sp, #4]
	ldr	r3, [r8]
	movs	r0, #0
	cmp	r2, r3
	bne	.L30
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L30:
	bl	__stack_chk_fail(PLT)
.L32:
	.align	3
.L31:
	.word	0
	.word	1093567616
	.word	0
	.word	1083129856
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC20+4)
	.word	__stack_chk_guard(GOT)
	.word	.LANCHOR0-(.LPIC21+4)
	.word	.LC0-(.LPIC25+4)
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
	.ascii	"\012\012Bind time %lf[ms]\012\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
