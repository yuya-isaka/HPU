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
	.file	"addr_test.c"
	.text
	.align	1
	.p2align 2,,3
	.global	printb
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	printb, %function
printb:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r7, r0
	ldr	r3, .L8
	movs	r5, #32
	ldr	r2, .L8+4
	mov	r4, #-2147483648
.LPIC0:
	add	r3, pc
	ldr	r6, [r3, r2]
.L3:
	tst	r4, r7
	ldr	r1, [r6]
	lsr	r4, r4, #1
	ite	ne
	movne	r0, #49
	moveq	r0, #48
	bl	_IO_putc(PLT)
	subs	r5, r5, #1
	bne	.L3
	pop	{r3, r4, r5, r6, r7, pc}
.L9:
	.align	2
.L8:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC0+4)
	.word	stdout(GOT)
	.size	printb, .-printb
	.align	1
	.p2align 2,,3
	.global	putb
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	putb, %function
putb:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r5, r0
	ldr	r3, .L12
	movs	r0, #48
	ldr	r2, .L12+4
.LPIC1:
	add	r3, pc
	ldr	r4, [r3, r2]
	ldr	r1, [r4]
	bl	_IO_putc(PLT)
	ldr	r1, [r4]
	movs	r0, #98
	bl	_IO_putc(PLT)
	mov	r0, r5
	bl	printb(PLT)
	ldr	r1, [r4]
	movs	r0, #10
	pop	{r3, r4, r5, lr}
	b	_IO_putc(PLT)
.L13:
	.align	2
.L12:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC1+4)
	.word	stdout(GOT)
	.size	putb, .-putb
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
	.global	shifter_ngram
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	shifter_ngram, %function
shifter_ngram:
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L31
	mov	ip, #0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
.LPIC10:
	add	r3, pc
	ldr	r4, .L31+4
	sub	sp, sp, #156
	ldr	r1, .L31+8
	add	r9, sp, #144
	str	r0, [sp, #4]
	mov	r6, ip
	ldr	r0, [r3, r4]
	add	r4, sp, #16
	ldr	r2, .L31+12
	mov	r10, ip
	str	r4, [sp]
	str	r0, [sp, #12]
	ldr	r0, [r0]
	str	r0, [sp, #148]
	ldr	r8, [r3, r1]
	ldr	r3, [r3, r2]
	str	r3, [sp, #8]
.L17:
	ldr	r4, [sp]
	mov	r5, r4
.L18:
	str	r10, [r4, #4]!
	cmp	r4, r9
	bne	.L18
	movs	r3, #1
	ldr	r0, [sp]
	lsl	r7, r3, r6
	rsb	lr, r6, #32
	subs	r7, r7, #1
	movs	r1, #0
.L19:
	add	r3, r8, r1, lsl #12
	ldr	fp, [r0, #4]!
	adds	r1, r1, #1
	ldr	r2, [r3, ip]
	cmp	r1, #1
	and	r3, r2, r7
	lsr	r2, r2, r6
	orr	r2, fp, r2
	str	r2, [r0]
	it	eq
	ldreq	r2, [sp, #144]
	lsl	r3, r3, lr
	itt	eq
	orreq	r3, r3, r2
	streq	r3, [sp, #144]
	beq	.L19
	ldr	r2, [r0, #-4]
	cmp	r1, #32
	orr	r3, r3, r2
	str	r3, [r0, #-4]
	bne	.L19
	ldr	r3, [sp, #8]
	add	r3, r3, ip
.L22:
	ldr	r2, [r5, #4]!
	cmp	r5, r4
	str	r2, [r3]
	add	r3, r3, #4096
	bne	.L22
	ldr	r3, [sp, #4]
	adds	r6, r6, #1
	add	ip, ip, #4
	cmp	r6, r3
	it	eq
	moveq	r6, #0
	cmp	ip, #4096
	bne	.L17
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #148]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L30
	add	sp, sp, #156
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L30:
	bl	__stack_chk_fail(PLT)
.L32:
	.align	2
.L31:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC10+4)
	.word	__stack_chk_guard(GOT)
	.word	item_memory_array(GOT)
	.word	item_memory_array_new(GOT)
	.size	shifter_ngram, .-shifter_ngram
	.align	1
	.p2align 2,,3
	.global	addition
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	addition, %function
addition:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	lsr	lr, r1, #1
	mov	ip, r0
	add	r6, r0, r1, lsl #2
	movs	r7, #32
	mov	r5, #-2147483648
	movs	r0, #0
.L34:
	mov	r2, ip
	movs	r4, #0
	cbz	r1, .L36
.L35:
	ldr	r3, [r2], #4
	ands	r3, r3, r5
	cmp	r3, #0
	it	ne
	addne	r4, r4, #1
	cmp	r6, r2
	bne	.L35
	cmp	lr, r4
	it	cc
	addcc	r0, r0, r5
.L36:
	subs	r7, r7, #1
	lsr	r5, r5, #1
	bne	.L34
	pop	{r4, r5, r6, r7, pc}
	.size	addition, .-addition
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
	cbnz	r0, .L47
	ldr	r3, .L48
	push	{r4, r5}
.LPIC15:
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
.L47:
	ldr	r3, .L48+4
	movw	r0, #52501
	movw	r2, #21989
	movt	r0, 1883
.LPIC11:
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
.L49:
	.align	2
.L48:
	.word	.LANCHOR0-(.LPIC15+4)
	.word	.LANCHOR0-(.LPIC11+4)
	.size	xor128, .-xor128
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
	cbz	r0, .L51
	cmp	r1, #1
	beq	.L67
	cmp	r1, #2
	beq	.L68
	cmp	r1, #4
	beq	.L69
	cmp	r1, #6
	beq	.L70
	cmp	r1, #12
	bne	.L57
	orr	r0, r2, #33792
	bx	lr
.L51:
	cmp	r1, #3
	beq	.L58
	cmp	r1, #5
	beq	.L59
	cmp	r1, #7
	beq	.L60
	cmp	r1, #8
	beq	.L61
	cmp	r1, #9
	beq	.L62
	cmp	r1, #10
	beq	.L63
	cmp	r1, #11
	beq	.L71
.L57:
	ldr	r1, .L72
	movs	r0, #1
	push	{r3, lr}
.LPIC23:
	add	r1, pc
	bl	__printf_chk(PLT)
	movs	r0, #0
	pop	{r3, pc}
.L67:
	orr	r0, r2, #49152
	bx	lr
.L58:
	mov	r0, #16384
	bx	lr
.L69:
	orr	r0, r2, #36864
	bx	lr
.L68:
	orr	r0, r2, #40960
	bx	lr
.L59:
	mov	r0, #8192
	bx	lr
.L60:
	mov	r0, #4096
	bx	lr
.L70:
	orr	r0, r2, #34816
	bx	lr
.L61:
	mov	r0, #2048
	bx	lr
.L62:
	mov	r0, #1024
	bx	lr
.L71:
	mov	r0, #256
	bx	lr
.L63:
	mov	r0, #512
	bx	lr
.L73:
	.align	2
.L72:
	.word	.LC0-(.LPIC23+4)
	.size	assemble, .-assemble
	.global	__aeabi_idiv
	.global	__aeabi_idivmod
	.align	1
	.p2align 2,,3
	.global	check
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	check, %function
check:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #68
	mov	r5, r0
	mov	r4, r1
	str	r0, [sp, #20]
	mov	r1, r5
	mov	r0, r2
	str	r3, [sp, #44]
	str	r2, [sp, #8]
	bl	__aeabi_idiv(PLT)
	mov	r1, r4
	mov	r5, r0
	bl	__aeabi_idivmod(PLT)
	and	r3, r5, #1
	str	r3, [sp, #16]
	ldr	r3, .L201
	str	r5, [sp, #24]
.LPIC24:
	add	r3, pc
	str	r3, [sp, #12]
	cbnz	r1, .L75
	subs	r0, r0, #1
.L75:
	ldr	r3, [sp, #20]
	mul	r3, r4, r3
	str	r3, [sp, #28]
	mul	r3, r0, r3
	str	r3, [sp, #32]
	ldr	r3, [sp, #16]
	cbnz	r3, .L76
	adds	r3, r5, #1
	str	r3, [sp, #24]
.L76:
	ldr	r0, [sp, #12]
	movs	r2, #4
	ldr	r3, .L201+4
	ldr	r3, [r0, r3]
	ldr	r0, [r3]
	str	r3, [sp, #52]
	str	r2, [r0, #48]
	str	r2, [r0]
.L77:
	ldr	r2, [r0]
	ands	r2, r2, #4
	bne	.L77
	ldr	r7, [sp, #12]
	mov	ip, #2
	ldr	r3, .L201+8
	ldr	r5, .L201+12
	ldr	r3, [r7, r3]
	str	r3, [sp, #60]
	ldr	r3, [r3]
	str	ip, [r3]
	ldr	r3, [r7, r5]
	ldr	r7, [sp, #16]
	str	r3, [sp, #56]
	ldr	r3, [r3]
	str	r3, [sp]
	cbnz	r7, .L78
	ldr	r2, [sp, #44]
	mvn	r5, r2, lsl #18
	mov	r2, r3
	mvn	r5, r5, lsr #18
	mov	r3, r7
	uxth	r6, r5
	mov	r5, r7
	cbz	r3, .L199
.L80:
	cmp	r3, #63
	strh	r5, [r2]	@ movhi
	beq	.L200
.L81:
	adds	r3, r3, #1
	adds	r2, r2, #2
	cmp	r3, #0
	bne	.L80
.L199:
	ldr	r7, [sp]
	strh	r6, [r7]	@ movhi
	b	.L81
.L200:
	ldr	r3, [sp]
	movs	r2, #64
	movs	r5, #0
	mov	r6, #2048
	adds	r3, r3, #128
	b	.L82
.L84:
	adds	r3, r3, #2
.L82:
	adds	r2, r2, #1
	cmp	r2, #65
	it	eq
	strheq	r6, [r3]	@ movhi
	beq	.L84
	cmp	r2, #128
	strh	r5, [r3]	@ movhi
	bne	.L84
.L78:
	ldr	r3, [sp, #8]
	cmp	r3, #0
	ble	.L85
	movs	r3, #0
	subs	r0, r1, r3
	mov	lr, r3
	mov	r9, #512
	it	ne
	movne	r0, #1
	str	r0, [sp, #48]
	ldr	r0, [sp, #28]
	mov	r8, #4096
	mov	ip, #2048
	subs	r0, r0, #1
	str	r0, [sp, #40]
	ldrh	r0, [sp, #20]
.L146:
	ldr	r5, [sp, #48]
	ldr	r7, [sp, #32]
	cmp	r7, lr
	ite	ne
	movne	r5, #0
	andeq	r5, r5, #1
	mov	r6, r5
	uxth	r5, lr
	cmp	r6, #0
	beq	.L86
	ldr	r7, [sp]
	lsls	r6, r2, #1
	str	r6, [sp, #4]
	add	r10, r7, r6
	mov	r7, r2
	movs	r6, #0
	str	r5, [sp, #36]
.L89:
	cmp	r1, r6
	add	r6, r6, #1
	itet	gt
	orrgt	fp, r5, #49152
	strhle	r3, [r10]	@ movhi
	strhgt	fp, [r10]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r10, r10, #2
	uxth	r5, r5
	bne	.L89
	ldr	r5, [sp, #4]
	mov	r10, #0
	add	r6, r5, #128
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, r10
.L92:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	r9, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L92
	ldr	r5, [sp, #36]
	ldr	r6, [sp, #4]
	adds	r5, r5, #1
	add	r10, r6, #256
	ldr	r6, [sp]
	uxth	r5, r5
	add	r10, r10, r6
	movs	r6, #0
.L95:
	cmp	r1, r6
	add	r6, r6, #1
	itet	gt
	orrgt	fp, r5, #40960
	strhle	r3, [r10]	@ movhi
	strhgt	fp, [r10]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r10, r10, #2
	uxth	r5, r5
	bne	.L95
	ldr	r5, [sp, #4]
	mov	r10, #0
	add	r6, r5, #384
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, r10
.L98:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	r8, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L98
	ldr	r5, [sp, #4]
	mov	r10, #0
	add	r6, r5, #512
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, r10
.L101:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	r9, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L101
	ldr	r5, [sp, #36]
	ldr	r6, [sp, #4]
	adds	r5, r5, #2
	add	r10, r6, #640
	ldr	r6, [sp]
	uxth	r5, r5
	add	r10, r10, r6
	movs	r6, #0
.L104:
	cmp	r1, r6
	add	r6, r6, #1
	itet	gt
	orrgt	fp, r5, #40960
	strhle	r3, [r10]	@ movhi
	strhgt	fp, [r10]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r10, r10, #2
	uxth	r5, r5
	bne	.L104
	ldr	r5, [sp, #4]
	mov	fp, #0
	mov	r10, #16384
	add	r6, r5, #768
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, fp
.L107:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	r10, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L107
	ldr	r5, [sp, #4]
	mov	r10, #0
	add	r6, r5, #896
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, r10
.L110:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	r8, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L110
	ldr	r5, [sp, #4]
	mov	r10, #0
	add	r6, r5, #1024
	ldr	r5, [sp]
	add	r6, r6, r5
	mov	r5, r10
.L113:
	cmp	r1, r5
	add	r5, r5, #1
	it	gt
	strhgt	ip, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L113
	ldr	r5, [sp, #4]
	add	r2, r2, #576
	mov	r10, #1024
	add	r6, r5, #1152
	ldr	r5, [sp]
	add	r6, r6, r5
	b	.L114
.L116:
	adds	r6, r6, #2
.L114:
	adds	r2, r2, #1
	mvn	r5, #576
	adds	r5, r2, r5
	cmp	r5, r7
	it	eq
	strheq	r10, [r6]	@ movhi
	beq	.L116
	sub	r5, r2, #640
	strh	r3, [r6]	@ movhi
	cmp	r5, r7
	bne	.L116
.L198:
	ldr	r6, [sp, #28]
	ldr	r5, [sp, #40]
	add	r5, r5, lr
	add	lr, lr, r6
	ldr	r6, [sp, #8]
	adds	r5, r5, #1
	cmp	r6, r5
	bgt	.L146
	ldr	r3, [sp, #56]
	ldr	r3, [r3]
	str	r3, [sp]
	ldr	r3, [sp, #52]
	ldr	r0, [r3]
.L85:
	ldr	r3, [sp]
	mov	r5, r2
	movs	r6, #0
	mov	r7, #1024
	add	r1, r3, r2, lsl #1
	b	.L147
.L149:
	adds	r1, r1, #2
.L147:
	adds	r2, r2, #1
	subs	r3, r2, #1
	cmp	r3, r5
	it	eq
	strheq	r7, [r1]	@ movhi
	beq	.L149
	subs	r3, r2, r5
	strh	r6, [r1]	@ movhi
	cmp	r3, #64
	bne	.L149
	ldr	r7, [sp, #12]
	movs	r1, #1
	ldr	r5, .L201+16
	lsls	r2, r2, r1
	str	r1, [r0]
	movs	r6, #128
	ldr	r3, .L201+20
	ldr	r5, [r7, r5]
	ldr	r5, [r5]
	str	r5, [r0, #24]
	str	r2, [r0, #40]
	str	r1, [r0, #48]
	ldr	r3, [r7, r3]
	ldr	r3, [r3]
	str	r3, [r0, #72]
	str	r6, [r0, #88]
.L150:
	ldr	r3, [r0, #52]
	lsls	r3, r3, #19
	bpl	.L150
	ldr	r3, .L201+24
	movs	r6, #0
	ldr	r1, [sp, #12]
	mov	r8, r6
	movw	r2, #4915
	movt	r2, 1353
	ldr	r5, [r1, r3]
	str	r2, [r5]
.L151:
	movs	r7, #0
.L154:
	orr	r3, r7, r8
	adds	r7, r7, #1
	cmp	r3, #0
	beq	.L154
	movs	r0, #0
	bl	xor128(PLT)
	add	r3, r6, r7, lsl #12
	sub	r3, r3, #4096
	cmp	r7, #32
	str	r0, [r5, r3]
	bne	.L154
	add	r8, r8, #1
	adds	r6, r6, #4
	cmp	r8, #1024
	bne	.L151
	ldr	r6, [sp, #20]
	mov	r9, #0
	ldr	r3, .L201+28
	mov	r0, r6
.LPIC25:
	add	r3, pc
	str	r3, [sp]
	bl	shifter_ngram(PLT)
	ldr	r3, .L201+32
.LPIC26:
	add	r3, pc
	str	r3, [sp, #4]
	ldr	r3, [sp, #44]
	lsl	fp, r3, #2
	ldr	r3, [sp, #24]
	strd	fp, r4, [sp, #20]
	ldr	fp, [sp, #12]
	lsl	r10, r3, #2
	lsrs	r7, r3, #1
	mov	r4, r3
	str	r5, [sp, #12]
.L166:
	mov	r0, r10
	bl	malloc(PLT)
	mov	r5, r0
	cmp	r0, #0
	beq	.L155
	ldr	r3, [sp, #8]
	cmp	r3, #0
	it	le
	movle	lr, #0
	ble	.L157
	ldr	r2, .L201+36
	mov	lr, #0
	ldr	r3, [sp, #8]
	mov	r1, lr
	ldr	r2, [fp, r2]
	add	r0, r3, r9, lsl #8
	mov	r3, lr
	sub	ip, r2, #4
	add	r2, ip, r9, lsl #10
	add	ip, ip, r0, lsl #2
.L159:
	ldr	r0, [r2, #4]!
	adds	r3, r3, #1
	cmp	r6, r3
	eor	r1, r1, r0
	itttt	eq
	streq	r1, [r5, lr, lsl #2]
	moveq	r1, #0
	addeq	lr, lr, #1
	moveq	r3, r1
	cmp	ip, r2
	bne	.L159
.L157:
	ldr	r3, [sp, #16]
	cbnz	r3, .L160
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #20]
	add	r3, r3, r9, lsl #10
	ldr	r3, [r3, r2]
	str	r3, [r5, lr, lsl #2]
.L160:
	add	lr, r10, r5
	mov	r8, #32
	movs	r2, #0
	mov	ip, #-2147483648
.L161:
	mov	r1, r5
	movs	r0, #0
	cbz	r4, .L163
.L162:
	ldr	r3, [r1], #4
	and	r3, r3, ip
	cmp	r3, #0
	it	ne
	addne	r0, r0, #1
	cmp	lr, r1
	bne	.L162
	cmp	r7, r0
	it	cc
	addcc	r2, r2, ip
.L163:
	subs	r8, r8, #1
	lsr	ip, ip, #1
	bne	.L161
	ldr	r3, .L201+40
	ldr	r3, [fp, r3]
	ldr	r3, [r3]
	ldr	r1, [r3, r9]
	cmp	r1, r2
	beq	.L165
	ldr	r3, [r3, r9]
	movs	r0, #1
	ldr	r1, [sp]
	bl	__printf_chk(PLT)
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #24]
	movs	r0, #1
	ldr	r1, [sp, #4]
	bl	__printf_chk(PLT)
.L165:
	mov	r0, r5
	add	r9, r9, #4
	bl	free(PLT)
	cmp	r9, #128
	bne	.L166
	ldr	r3, [sp, #60]
	movs	r2, #0
	ldr	r3, [r3]
	str	r2, [r3]
	add	sp, sp, #68
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L86:
	ldr	r7, [sp]
	lsl	fp, r2, #1
	str	r5, [sp, #4]
	add	r7, r7, fp
.L120:
	cmp	r4, r6
	add	r6, r6, #1
	itet	gt
	orrgt	r10, r5, #49152
	strhle	r3, [r7]	@ movhi
	strhgt	r10, [r7]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r7, r7, #2
	uxth	r5, r5
	bne	.L120
	ldr	r7, [sp]
	add	r6, fp, #128
	movs	r5, #0
	add	r6, r6, r7
.L123:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	r9, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L123
	ldr	r5, [sp, #4]
	add	r7, fp, #256
	ldr	r6, [sp]
	adds	r5, r5, #1
	add	r7, r7, r6
	movs	r6, #0
	uxth	r5, r5
.L126:
	cmp	r4, r6
	add	r6, r6, #1
	itet	gt
	orrgt	r10, r5, #40960
	strhle	r3, [r7]	@ movhi
	strhgt	r10, [r7]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r7, r7, #2
	uxth	r5, r5
	bne	.L126
	ldr	r7, [sp]
	add	r6, fp, #384
	movs	r5, #0
	add	r6, r6, r7
.L129:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	r8, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L129
	ldr	r7, [sp]
	add	r6, fp, #512
	movs	r5, #0
	add	r6, r6, r7
.L132:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	r9, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L132
	ldr	r5, [sp, #4]
	add	r7, fp, #640
	ldr	r6, [sp]
	adds	r5, r5, #2
	add	r7, r7, r6
	movs	r6, #0
	uxth	r5, r5
.L135:
	cmp	r4, r6
	add	r6, r6, #1
	itet	gt
	orrgt	r10, r5, #40960
	strhle	r3, [r7]	@ movhi
	strhgt	r10, [r7]	@ movhi
	add	r5, r5, r0
	cmp	r6, #64
	add	r7, r7, #2
	uxth	r5, r5
	bne	.L135
	ldr	r7, [sp]
	add	r6, fp, #768
	movs	r5, #0
	add	r6, r6, r7
	mov	r7, #16384
.L138:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	r7, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L138
	ldr	r7, [sp]
	add	r6, fp, #896
	movs	r5, #0
	add	r6, r6, r7
.L141:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	r8, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L141
	ldr	r7, [sp]
	add	r6, fp, #1024
	movs	r5, #0
	add	r6, r6, r7
.L145:
	cmp	r4, r5
	add	r5, r5, #1
	it	gt
	strhgt	ip, [r6]	@ movhi
	add	r6, r6, #2
	it	le
	strhle	r3, [r6, #-2]	@ movhi
	cmp	r5, #64
	bne	.L145
	add	r2, r2, #576
	b	.L198
.L155:
	bl	exit(PLT)
.L202:
	.align	2
.L201:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC24+4)
	.word	dma(GOT)
	.word	top(GOT)
	.word	src(GOT)
	.word	src_phys(GOT)
	.word	dst_phys(GOT)
	.word	item_memory_array(GOT)
	.word	.LC1-(.LPIC25+4)
	.word	.LC2-(.LPIC26+4)
	.word	item_memory_array_new(GOT)
	.word	dst(GOT)
	.size	check, .-check
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
	@ args = 0, pretend = 0, frame = 1032
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subw	sp, sp, #1044
	ldr	r4, .L244
	ldr	r3, .L244+4
.LPIC27:
	add	r4, pc
	ldr	r0, .L244+8
	ldr	fp, [r4, r3]
.LPIC28:
	add	r0, pc
	ldr	r3, [fp]
	str	r3, [sp, #1036]
	bl	puts(PLT)
	ldr	r0, .L244+12
	movs	r1, #0
.LPIC29:
	add	r0, pc
	bl	open(PLT)
	adds	r1, r0, #1
	bne	.L231
.L204:
	ldr	r0, .L244+16
	movs	r1, #0
.LPIC32:
	add	r0, pc
	bl	open(PLT)
	adds	r2, r0, #1
	mov	r6, r0
	bne	.L232
.L206:
	ldr	r0, .L244+20
	movs	r1, #2
.LPIC35:
	add	r0, pc
	bl	open(PLT)
	subs	r5, r0, #0
	blt	.L233
	ldr	r0, .L244+24
	movs	r1, #2
.LPIC37:
	add	r0, pc
	bl	open(PLT)
	subs	r7, r0, #0
	blt	.L234
	ldr	r0, .L244+28
	movw	r1, #4098
	movt	r1, 16
.LPIC39:
	add	r0, pc
	bl	open(PLT)
	subs	r8, r0, #0
	blt	.L235
	ldr	r0, .L244+32
	movw	r1, #4098
	movt	r1, 16
.LPIC41:
	add	r0, pc
	bl	open(PLT)
	subs	r9, r0, #0
	blt	.L236
	movs	r6, #0
	movs	r3, #1
	strd	r9, r6, [sp]
	mov	r0, r6
	movs	r2, #3
	mov	r1, #4096
	bl	mmap(PLT)
	ldr	r3, .L244+36
	ldr	r10, [r4, r3]
	str	r0, [r10]
	adds	r0, r0, #1
	beq	.L237
	movs	r3, #1
	str	r6, [sp, #4]
	str	r8, [sp]
	movs	r2, #3
	mov	r1, #4096
	mov	r0, r6
	bl	mmap(PLT)
	ldr	r3, .L244+40
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L238
	movs	r3, #1
	str	r6, [sp, #4]
	str	r5, [sp]
	movs	r2, #3
	mov	r1, #524288
	mov	r0, r6
	bl	mmap(PLT)
	ldr	r3, .L244+44
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L239
	movs	r3, #1
	str	r6, [sp, #4]
	mov	r0, r6
	str	r7, [sp]
	movs	r2, #3
	mov	r1, #524288
	bl	mmap(PLT)
	ldr	r3, .L244+48
	ldr	r3, [r4, r3]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L240
	ldr	r2, [r10]
	movw	r1, #1023
	movs	r3, #1
	str	r1, [r2, #4]
	str	r3, [r2]
.L217:
	ldr	r3, [r2]
	lsls	r3, r3, #31
	bmi	.L217
	ldr	r5, .L244+52
	movw	r10, #52501
	movw	r9, #21989
	movw	r8, #15285
	movw	r7, #4915
	movt	r10, 1883
	movt	r9, 5530
	movt	r8, 7954
	movt	r7, 1353
.LPIC47:
	add	r5, pc
	movs	r6, #1
.L218:
	movs	r4, #3
.L219:
	movw	r3, #1023
	mov	r2, r4
	mov	r1, r6
	adds	r4, r4, #3
	movs	r0, #3
	bl	check(PLT)
	movw	r3, #1026
	cmp	r4, r3
	strd	r10, r9, [r5]
	strd	r8, r7, [r5, #8]
	bne	.L219
	adds	r6, r6, #1
	cmp	r6, #17
	bne	.L218
	ldr	r0, .L244+56
.LPIC51:
	add	r0, pc
	bl	puts(PLT)
	ldr	r0, .L244+60
.LPIC52:
	add	r0, pc
	bl	puts(PLT)
	b	.L209
.L234:
	ldr	r0, .L244+64
.LPIC38:
	add	r0, pc
	bl	perror(PLT)
.L209:
	ldr	r2, [sp, #1036]
	movs	r0, #0
	ldr	r3, [fp]
	cmp	r2, r3
	bne	.L241
	addw	sp, sp, #1044
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L232:
	add	r5, sp, #12
	mov	r2, #1024
	mov	r1, r5
	bl	read(PLT)
	cmp	r0, #0
	blt	.L242
.L207:
	ldr	r3, .L244+68
	mov	r0, r5
	ldr	r1, .L244+72
	ldr	r2, [r4, r3]
.LPIC34:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r6
	bl	close(PLT)
	b	.L206
.L231:
	add	r5, sp, #12
	mov	r2, #1024
	mov	r6, r0
	mov	r1, r5
	bl	read(PLT)
	cmp	r0, #0
	blt	.L243
.L205:
	ldr	r3, .L244+76
	mov	r0, r5
	ldr	r1, .L244+80
	ldr	r2, [r4, r3]
.LPIC31:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r6
	bl	close(PLT)
	b	.L204
.L233:
	ldr	r0, .L244+84
.LPIC36:
	add	r0, pc
	bl	perror(PLT)
	b	.L209
.L237:
	ldr	r0, .L244+88
.LPIC43:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r9
	bl	close(PLT)
	b	.L209
.L235:
	ldr	r0, .L244+92
.LPIC40:
	add	r0, pc
	bl	perror(PLT)
	b	.L209
.L243:
	ldr	r0, .L244+96
.LPIC30:
	add	r0, pc
	bl	perror(PLT)
	b	.L205
.L242:
	ldr	r0, .L244+100
.LPIC33:
	add	r0, pc
	bl	perror(PLT)
	b	.L207
.L236:
	ldr	r0, .L244+104
.LPIC42:
	add	r0, pc
	bl	perror(PLT)
	b	.L209
.L238:
	ldr	r0, .L244+108
.LPIC44:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r8
	bl	close(PLT)
	b	.L209
.L239:
	ldr	r0, .L244+112
.LPIC45:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r5
	bl	close(PLT)
	b	.L209
.L240:
	ldr	r0, .L244+116
.LPIC46:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r7
	bl	close(PLT)
	b	.L209
.L241:
	bl	__stack_chk_fail(PLT)
.L245:
	.align	2
.L244:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC27+4)
	.word	__stack_chk_guard(GOT)
	.word	.LC3-(.LPIC28+4)
	.word	.LC4-(.LPIC29+4)
	.word	.LC7-(.LPIC32+4)
	.word	.LC9-(.LPIC35+4)
	.word	.LC11-(.LPIC37+4)
	.word	.LC13-(.LPIC39+4)
	.word	.LC15-(.LPIC41+4)
	.word	top(GOT)
	.word	dma(GOT)
	.word	src(GOT)
	.word	dst(GOT)
	.word	.LANCHOR0-(.LPIC47+4)
	.word	.LC21-(.LPIC51+4)
	.word	.LC22-(.LPIC52+4)
	.word	.LC12-(.LPIC38+4)
	.word	dst_phys(GOT)
	.word	.LC6-(.LPIC34+4)
	.word	src_phys(GOT)
	.word	.LC6-(.LPIC31+4)
	.word	.LC10-(.LPIC36+4)
	.word	.LC17-(.LPIC43+4)
	.word	.LC14-(.LPIC40+4)
	.word	.LC5-(.LPIC30+4)
	.word	.LC8-(.LPIC33+4)
	.word	.LC16-(.LPIC42+4)
	.word	.LC18-(.LPIC44+4)
	.word	.LC19-(.LPIC45+4)
	.word	.LC20-(.LPIC46+4)
	.size	main, .-main
	.comm	dst_phys,4,4
	.comm	src_phys,4,4
	.comm	dst,4,4
	.comm	src,4,4
	.comm	dma,4,4
	.comm	top,4,4
	.comm	item_memory_array_new,131072,4
	.comm	item_memory_array,131072,4
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	x.7715, %object
	.size	x.7715, 4
x.7715:
	.word	123456789
	.type	y.7716, %object
	.size	y.7716, 4
y.7716:
	.word	362436069
	.type	z.7717, %object
	.size	z.7717, 4
z.7717:
	.word	521288629
	.type	w.7718, %object
	.size	w.7718, 4
w.7718:
	.word	88675123
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"error\000"
	.space	2
.LC1:
	.ascii	"\012  Error %u %u\012\000"
.LC2:
	.ascii	"  CORENUM=%d  ADDRNUM=%d\012\012\000"
	.space	1
.LC3:
	.ascii	"\012 ------------------------------ \351\226\213\345"
	.ascii	"\247\213 -------------------------------- \012\000"
	.space	1
.LC4:
	.ascii	"/sys/class/u-dma-buf/udmabuf0/phys_addr\000"
.LC5:
	.ascii	"Failed: read /sys/class/u-dma-buf/udmabuf0/phys_add"
	.ascii	"r\000"
	.space	3
.LC6:
	.ascii	"%lx\000"
.LC7:
	.ascii	"/sys/class/u-dma-buf/udmabuf1/phys_addr\000"
.LC8:
	.ascii	"Failed: read /sys/class/u-dma-buf/udmabuf1/phys_add"
	.ascii	"r\000"
	.space	3
.LC9:
	.ascii	"/dev/udmabuf0\000"
	.space	2
.LC10:
	.ascii	"Failed: open /dev/udmabuf0\000"
	.space	1
.LC11:
	.ascii	"/dev/udmabuf1\000"
	.space	2
.LC12:
	.ascii	"Failed: open /dev/udmabuf1\000"
	.space	1
.LC13:
	.ascii	"/dev/uio0\000"
	.space	2
.LC14:
	.ascii	"Falied: open /dev/uio0\000"
	.space	1
.LC15:
	.ascii	"/dev/uio1\000"
	.space	2
.LC16:
	.ascii	"Failed: open /dev/uio1\000"
	.space	1
.LC17:
	.ascii	"mmap top\000"
	.space	3
.LC18:
	.ascii	"mmap dma\000"
	.space	3
.LC19:
	.ascii	"mmap src\000"
	.space	3
.LC20:
	.ascii	"mmap dst\000"
	.space	3
.LC21:
	.ascii	"\012OK!\000"
	.space	3
.LC22:
	.ascii	"\012 ------------------------------ \347\265\202\344"
	.ascii	"\272\206 -------------------------------- \012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
