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
	.file	"perm_and_bound.c"
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
	.global	shifter_32
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	shifter_32, %function
shifter_32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r3, #1
	mov	r2, r0
	lsls	r3, r3, r1
	ldr	r0, [r0]
	subs	r3, r3, #1
	ands	r3, r3, r0
	push	{r4}
	rsb	r4, r1, #32
	lsls	r3, r3, r4
	lsrs	r0, r0, r1
	str	r3, [r2]
	ldr	r4, [sp], #4
	bx	lr
	.size	shifter_32, .-shifter_32
	.align	1
	.p2align 2,,3
	.global	shifter_1024
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	shifter_1024, %function
shifter_1024:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r9, r0
	mov	r4, r1
	mov	r0, r2
	movs	r1, #4
	mov	r8, r2
	mov	r10, r3
	bl	calloc(PLT)
	cmp	r8, #0
	beq	.L24
	add	r7, r8, #1073741824
	ldr	r2, [r4]
	subs	r7, r7, #1
	movs	r3, #1
	lsl	r3, r3, r10
	sub	ip, r2, #4
	lsls	r7, r7, #2
	subs	r3, r3, #1
	add	fp, r0, r7
	rsb	lr, r10, #32
	subs	r1, r0, #4
	movs	r4, #0
.L27:
	ldr	r2, [ip, #4]!
	ldr	r6, [r1, #4]!
	and	r5, r2, r3
	lsr	r2, r2, r10
	orrs	r2, r2, r6
	lsl	r5, r5, lr
	str	r2, [r1]
	cbz	r4, .L35
	ldr	r6, [r1, #-4]
	orrs	r5, r5, r6
	str	r5, [r1, #-4]
.L26:
	adds	r4, r4, #1
	cmp	r4, r8
	bne	.L27
	ldr	r2, [r9]
	adds	r7, r7, #4
	add	r7, r7, r0
	mov	r3, r0
	subs	r2, r2, #4
.L28:
	ldr	r1, [r3], #4
	cmp	r7, r3
	str	r1, [r2, #4]!
	bne	.L28
.L24:
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	free(PLT)
.L35:
	ldr	r2, [fp]
	orrs	r5, r5, r2
	str	r5, [fp]
	b	.L26
	.size	shifter_1024, .-shifter_1024
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
.L37:
	mov	r2, ip
	movs	r4, #0
	cbz	r1, .L39
.L38:
	ldr	r3, [r2], #4
	ands	r3, r3, r5
	cmp	r3, #0
	it	ne
	addne	r4, r4, #1
	cmp	r6, r2
	bne	.L38
	cmp	lr, r4
	it	cc
	addcc	r0, r0, r5
.L39:
	subs	r7, r7, #1
	lsr	r5, r5, #1
	bne	.L37
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
	ldr	r2, .L70+16
	ldr	r3, .L70+20
.LPIC20:
	add	r2, pc
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #164
	ldr	r3, [r2, r3]
	add	r6, sp, #16
	movw	r4, #4915
	movt	r4, 1353
	mov	r8, #0
	str	r3, [sp, #12]
	mov	r7, r4
	ldr	r3, [r3]
	str	r3, [sp, #156]
	bl	clock(PLT)
	str	r0, [sp, #8]
	movs	r0, #10
	bl	srand(PLT)
	ldr	r3, .L70+24
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
.L45:
	lsl	r9, r8, #2
	movs	r4, #0
.L49:
	orr	r3, r4, r8
	lsls	r5, r4, #2
	adds	r4, r4, #1
	cbnz	r3, .L68
.L46:
	ldr	r3, [sp, #16]
	ldr	r3, [r3, r9]
	str	r7, [r3, r5]
	orr	r3, r4, r8
	lsls	r5, r4, #2
	adds	r4, r4, #1
	cmp	r3, #0
	beq	.L46
.L68:
	movs	r0, #0
	bl	xor128(PLT)
	ldr	r3, [sp, #16]
	cmp	r4, #32
	ldr	r3, [r3, r9]
	str	r0, [r3, r5]
	bne	.L49
	add	r8, r8, #1
	cmp	r8, #1024
	bne	.L45
	add	r7, sp, #20
	mov	r2, r4
	movw	r1, #61568
	movt	r1, 762
	mov	r0, r7
	mov	r8, #49664
	bl	makeArrayInt(PLT)
	movt	r8, 3051
	movs	r5, #0
.L50:
	bl	rand(PLT)
	mov	r4, r0
	bl	rand(PLT)
	ubfx	ip, r4, #0, #10
	ldr	r1, [sp, #16]
	rsbs	r2, r0, #0
	and	r3, r0, #31
	and	r0, r2, #31
	mov	r2, #32
	it	pl
	rsbpl	r3, r0, #0
	rsbs	r4, r4, #0
	ubfx	r4, r4, #0, #10
	ldr	r0, [sp, #20]
	it	pl
	rsbpl	ip, r4, #0
	add	r0, r0, r5
	adds	r5, r5, #4
	add	r1, r1, ip, lsl #2
	bl	shifter_1024(PLT)
	cmp	r5, r8
	bne	.L50
	add	r4, sp, #24
	movw	r2, #61568
	movs	r1, #32
	movt	r2, 762
	mov	r0, r4
	bl	makeArrayInt(PLT)
	ldrd	r3, ip, [sp, #20]
	movw	r0, #49660
	movt	r0, 3051
	add	r9, ip, #128
	add	r0, r0, r3
	sub	r8, r3, #4
	mov	lr, ip
.L51:
	sub	r5, lr, ip
	ldr	r2, [lr], #4
	mov	r3, r8
	subs	r2, r2, #4
.L52:
	ldr	r1, [r3, #4]!
	cmp	r0, r3
	ldr	r1, [r1, r5]
	str	r1, [r2, #4]!
	bne	.L52
	cmp	r9, lr
	bne	.L51
	movw	fp, #30784
	movt	fp, 381
	mov	r8, r4
	mov	r5, r4
	sub	r3, ip, #4
	str	r3, [sp]
	add	r3, sp, #152
	str	r3, [sp, #4]
.L58:
	ldr	r2, [sp]
	movw	ip, #49660
	movt	ip, 3051
	mov	lr, #32
	mov	r10, #0
	mov	r0, #-2147483648
	ldr	r3, [r2, #4]!
	add	ip, ip, r3
	sub	r9, r3, #4
	str	r2, [sp]
.L54:
	mov	r2, r9
	movs	r1, #0
.L55:
	ldr	r3, [r2, #4]!
	ands	r3, r3, r0
	cmp	r3, #0
	it	ne
	addne	r1, r1, #1
	cmp	ip, r2
	bne	.L55
	cmp	r1, fp
	it	gt
	addgt	r10, r10, r0
	subs	lr, lr, #1
	lsr	r0, r0, #1
	bne	.L54
	ldr	r3, [sp, #4]
	str	r10, [r5, #4]!
	cmp	r3, r5
	bne	.L58
	ldr	r9, .L70+28
.LPIC25:
	add	r9, pc
.L59:
	ldr	r2, [r8, #4]!
	mov	r1, r9
	movs	r0, #1
	bl	__printf_chk(PLT)
	cmp	r5, r8
	bne	.L59
	mov	r0, r4
	movs	r1, #32
	bl	freeArrayInt(PLT)
	mov	r0, r7
	movw	r1, #61568
	movt	r1, 762
	bl	freeArrayInt(PLT)
	mov	r1, #1024
	mov	r0, r6
	bl	freeArrayInt(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #8]
	vldr.64	d4, .L70
	ldr	r1, .L70+32
	vldr.64	d6, .L70+8
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
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #156]
	movs	r0, #0
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L69
	add	sp, sp, #164
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L69:
	bl	__stack_chk_fail(PLT)
.L71:
	.align	3
.L70:
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
	.ascii	"\012\012Permu time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
