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
	.file	"bind.c"
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
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L35+16
	ldr	r3, .L35+20
.LPIC20:
	add	r2, pc
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #28
	ldr	r3, [r2, r3]
	add	r8, sp, #12
	movw	r4, #4915
	movt	r4, 1353
	mov	r9, #0
	str	r3, [sp, #4]
	mov	r7, r4
	ldr	r3, [r3]
	str	r3, [sp, #20]
	bl	clock(PLT)
	mov	r6, r0
	movs	r0, #10
	bl	srand(PLT)
	ldr	r3, .L35+24
	movw	r1, #52501
	mov	r0, r8
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
	movs	r5, #0
	lsl	fp, r9, #2
	mov	r4, r5
	b	.L26
.L23:
	ldr	r3, [sp, #12]
	ldr	r3, [r3, fp]
	str	r7, [r3, r5]
.L24:
	adds	r5, r5, #4
.L26:
	orr	r3, r9, r4
	adds	r4, r4, #1
	cmp	r3, #0
	beq	.L23
	movs	r0, #0
	bl	xor128(PLT)
	ldr	r3, [sp, #12]
	cmp	r4, #32
	ldr	r3, [r3, fp]
	str	r0, [r3, r5]
	bne	.L24
	add	r9, r9, #1
	cmp	r9, #1024
	bne	.L22
	add	r5, sp, #16
	mov	r2, r4
	movw	r1, #61568
	movt	r1, 762
	mov	r0, r5
	mov	r4, #49664
	bl	makeArrayInt(PLT)
	movt	r4, 3051
	mov	r9, #0
.L28:
	bl	rand(PLT)
	mov	r10, r0
	bl	rand(PLT)
	rsbs	r2, r10, #0
	ubfx	ip, r10, #0, #10
	ubfx	r2, r2, #0, #10
	ldr	r1, [sp, #12]
	it	pl
	rsbpl	ip, r2, #0
	ldr	r2, [sp, #16]
	ldr	r7, [r1, ip, lsl #2]
	add	ip, r7, #124
	ubfx	r3, r0, #0, #10
	rsbs	r0, r0, #0
	ubfx	r0, r0, #0, #10
	it	pl
	rsbpl	r3, r0, #0
	ldr	r0, [r2, r9]
	subs	r2, r7, #4
	ldr	r1, [r1, r3, lsl #2]
	subs	r0, r0, #4
	subs	r1, r1, #4
.L27:
	ldr	r3, [r2, #4]!
	ldr	r7, [r1, #4]!
	cmp	r2, ip
	eor	r3, r3, r7
	str	r3, [r0, #4]!
	bne	.L27
	add	r9, r9, #4
	cmp	r9, r4
	bne	.L28
	mov	r0, r5
	movw	r1, #61568
	movt	r1, 762
	bl	freeArrayInt(PLT)
	mov	r1, #1024
	mov	r0, r8
	bl	freeArrayInt(PLT)
	bl	clock(PLT)
	vldr.64	d4, .L35
	ldr	r1, .L35+28
	vldr.64	d6, .L35+8
.LPIC25:
	add	r1, pc
	subs	r6, r0, r6
	movs	r0, #1
	vmov	s15, r6	@ int
	vcvt.f64.s32	d7, s15
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	ldr	r3, [sp, #4]
	ldr	r2, [sp, #20]
	movs	r0, #0
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L34
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L34:
	bl	__stack_chk_fail(PLT)
.L36:
	.align	3
.L35:
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
	.ascii	"\012\012Bind time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
