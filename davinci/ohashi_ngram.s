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
	.file	"ohashi_ngram.c"
	.text
	.align	1
	.p2align 2,,3
	.global	makeArray
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	makeArray, %function
makeArray:
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
	movs	r1, #2
	mov	r0, r6
	bl	calloc(PLT)
	str	r0, [r4], #4
	cmp	r5, r4
	bne	.L3
.L1:
	pop	{r4, r5, r6, pc}
	.size	makeArray, .-makeArray
	.align	1
	.p2align 2,,3
	.global	freeArray
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	freeArray, %function
freeArray:
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
	.size	freeArray, .-freeArray
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
	push	{r3, r4, r5, lr}
	mov	r4, r1
	ldr	r1, .L45
	mov	r5, r0
.LPIC8:
	add	r1, pc
	bl	strcmp(PLT)
	cbnz	r0, .L43
	orr	r0, r4, #49152
	pop	{r3, r4, r5, pc}
.L43:
	ldr	r1, .L45+4
	mov	r0, r5
.LPIC9:
	add	r1, pc
	bl	strcmp(PLT)
	cbnz	r0, .L44
	orr	r0, r4, #40960
	pop	{r3, r4, r5, pc}
.L44:
	ldr	r1, .L45+8
	mov	r0, r5
.LPIC10:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L17
	ldr	r1, .L45+12
	mov	r0, r5
.LPIC11:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L18
	ldr	r1, .L45+16
	mov	r0, r5
.LPIC12:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L19
	ldr	r1, .L45+20
	mov	r0, r5
.LPIC13:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L20
	ldr	r1, .L45+24
	mov	r0, r5
.LPIC14:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L21
	ldr	r1, .L45+28
	mov	r0, r5
.LPIC15:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L22
	ldr	r1, .L45+32
	mov	r0, r5
.LPIC16:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L23
	ldr	r1, .L45+36
	mov	r0, r5
.LPIC17:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L24
	ldr	r1, .L45+40
	mov	r0, r5
.LPIC18:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L25
	ldr	r1, .L45+44
	mov	r0, r5
.LPIC19:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L26
	ldr	r1, .L45+48
	mov	r0, r5
.LPIC20:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L27
	ldr	r1, .L45+52
	mov	r0, r5
.LPIC21:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L28
	ldr	r1, .L45+56
	mov	r0, r5
.LPIC22:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L29
	ldr	r1, .L45+60
	mov	r0, r5
.LPIC23:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L30
	ldr	r1, .L45+64
	mov	r0, r5
.LPIC24:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L31
	ldr	r1, .L45+68
	mov	r0, r5
.LPIC25:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L32
	ldr	r1, .L45+72
	mov	r0, r5
.LPIC26:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L33
	ldr	r1, .L45+76
	mov	r0, r5
.LPIC27:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L34
	ldr	r1, .L45+80
	mov	r0, r5
.LPIC28:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L35
	ldr	r1, .L45+84
	mov	r0, r5
.LPIC29:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L36
	ldr	r1, .L45+88
	mov	r0, r5
.LPIC30:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L37
	ldr	r1, .L45+92
	mov	r0, r5
.LPIC31:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L38
	ldr	r1, .L45+96
	mov	r0, r5
.LPIC32:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L39
	ldr	r1, .L45+100
	mov	r0, r5
.LPIC33:
	add	r1, pc
	bl	strcmp(PLT)
	cmp	r0, #0
	beq	.L40
	ldr	r1, .L45+104
	movs	r0, #1
.LPIC34:
	add	r1, pc
	bl	__printf_chk(PLT)
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L17:
	mov	r0, #4096
	pop	{r3, r4, r5, pc}
.L18:
	mov	r0, #2048
	pop	{r3, r4, r5, pc}
.L21:
	mov	r0, #256
	pop	{r3, r4, r5, pc}
.L19:
	mov	r0, #1024
	pop	{r3, r4, r5, pc}
.L20:
	mov	r0, #512
	pop	{r3, r4, r5, pc}
.L22:
	mov	r0, #20480
	pop	{r3, r4, r5, pc}
.L23:
	mov	r0, #18432
	pop	{r3, r4, r5, pc}
.L24:
	mov	r0, #17408
	pop	{r3, r4, r5, pc}
.L25:
	mov	r0, #16896
	pop	{r3, r4, r5, pc}
.L26:
	mov	r0, #16640
	pop	{r3, r4, r5, pc}
.L27:
	mov	r0, #16512
	pop	{r3, r4, r5, pc}
.L28:
	movw	r0, #16448
	pop	{r3, r4, r5, pc}
.L29:
	movw	r0, #16416
	pop	{r3, r4, r5, pc}
.L30:
	movw	r0, #16400
	pop	{r3, r4, r5, pc}
.L31:
	movw	r0, #16392
	pop	{r3, r4, r5, pc}
.L32:
	mov	r0, #12288
	pop	{r3, r4, r5, pc}
.L33:
	mov	r0, #10240
	pop	{r3, r4, r5, pc}
.L34:
	mov	r0, #9216
	pop	{r3, r4, r5, pc}
.L35:
	mov	r0, #8704
	pop	{r3, r4, r5, pc}
.L36:
	mov	r0, #8448
	pop	{r3, r4, r5, pc}
.L40:
	movw	r0, #8208
	pop	{r3, r4, r5, pc}
.L37:
	mov	r0, #8320
	pop	{r3, r4, r5, pc}
.L39:
	movw	r0, #8224
	pop	{r3, r4, r5, pc}
.L38:
	mov	r0, #8256
	pop	{r3, r4, r5, pc}
.L46:
	.align	2
.L45:
	.word	.LC3-(.LPIC8+4)
	.word	.LC4-(.LPIC9+4)
	.word	.LC5-(.LPIC10+4)
	.word	.LC6-(.LPIC11+4)
	.word	.LC7-(.LPIC12+4)
	.word	.LC8-(.LPIC13+4)
	.word	.LC9-(.LPIC14+4)
	.word	.LC10-(.LPIC15+4)
	.word	.LC11-(.LPIC16+4)
	.word	.LC12-(.LPIC17+4)
	.word	.LC13-(.LPIC18+4)
	.word	.LC14-(.LPIC19+4)
	.word	.LC15-(.LPIC20+4)
	.word	.LC16-(.LPIC21+4)
	.word	.LC17-(.LPIC22+4)
	.word	.LC18-(.LPIC23+4)
	.word	.LC19-(.LPIC24+4)
	.word	.LC20-(.LPIC25+4)
	.word	.LC21-(.LPIC26+4)
	.word	.LC22-(.LPIC27+4)
	.word	.LC23-(.LPIC28+4)
	.word	.LC24-(.LPIC29+4)
	.word	.LC25-(.LPIC30+4)
	.word	.LC26-(.LPIC31+4)
	.word	.LC27-(.LPIC32+4)
	.word	.LC28-(.LPIC33+4)
	.word	.LC29-(.LPIC34+4)
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
	@ args = 0, pretend = 0, frame = 1128
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subw	sp, sp, #1140
	ldr	fp, .L157+16
	ldr	r3, .L157+20
.LPIC51:
	add	fp, pc
	ldr	r3, [fp, r3]
	str	r3, [sp, #12]
	ldr	r3, [r3]
	str	r3, [sp, #1132]
	bl	clock(PLT)
	str	r0, [sp, #24]
	ldr	r0, .L157+24
.LPIC52:
	add	r0, pc
	bl	puts(PLT)
	ldr	r0, .L157+28
	movs	r1, #0
.LPIC53:
	add	r0, pc
	bl	open(PLT)
	adds	r4, r0, #1
	beq	.L48
	add	r5, sp, #108
	mov	r2, #1024
	mov	r4, r0
	mov	r1, r5
	bl	read(PLT)
	cmp	r0, #0
	blt	.L140
	ldr	r3, .L157+32
	mov	r0, r5
	ldr	r1, .L157+36
	ldr	r2, [fp, r3]
.LPIC55:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r4
	bl	close(PLT)
.L48:
	ldr	r0, .L157+40
	movs	r1, #0
.LPIC56:
	add	r0, pc
	bl	open(PLT)
	adds	r1, r0, #1
	mov	r4, r0
	beq	.L50
	add	r5, sp, #108
	mov	r2, #1024
	mov	r1, r5
	bl	read(PLT)
	cmp	r0, #0
	blt	.L141
	ldr	r3, .L157+44
	mov	r0, r5
	ldr	r1, .L157+48
	ldr	r2, [fp, r3]
.LPIC58:
	add	r1, pc
	bl	__isoc99_sscanf(PLT)
	mov	r0, r4
	bl	close(PLT)
.L50:
	ldr	r0, .L157+52
	movs	r1, #2
.LPIC59:
	add	r0, pc
	bl	open(PLT)
	subs	r5, r0, #0
	blt	.L142
	ldr	r0, .L157+56
	movs	r1, #2
.LPIC61:
	add	r0, pc
	bl	open(PLT)
	subs	r6, r0, #0
	blt	.L143
	ldr	r0, .L157+60
	movw	r1, #4098
	movt	r1, 16
.LPIC63:
	add	r0, pc
	bl	open(PLT)
	subs	r7, r0, #0
	blt	.L144
	ldr	r0, .L157+64
	movw	r1, #4098
	movt	r1, 16
.LPIC65:
	add	r0, pc
	bl	open(PLT)
	subs	r8, r0, #0
	blt	.L145
	movs	r4, #0
	movs	r3, #1
	strd	r8, r4, [sp]
	mov	r0, r4
	movs	r2, #3
	mov	r1, #4096
	bl	mmap(PLT)
	ldr	r3, .L157+68
	ldr	r3, [fp, r3]
	str	r3, [sp, #32]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L146
	movs	r3, #1
	str	r4, [sp, #4]
	str	r7, [sp]
	movs	r2, #3
	mov	r1, #4096
	mov	r0, r4
	bl	mmap(PLT)
	ldr	r3, .L157+72
	ldr	r3, [fp, r3]
	str	r3, [sp, #36]
	str	r0, [r3]
	adds	r0, r0, #1
	beq	.L147
	movs	r3, #1
	str	r4, [sp, #4]
	mov	r1, #25856
	str	r5, [sp]
	movt	r1, 7629
	movs	r2, #3
	mov	r0, r4
	bl	mmap(PLT)
	ldr	r3, .L157+76
	ldr	r8, [fp, r3]
	str	r0, [r8]
	adds	r0, r0, #1
	beq	.L148
	movs	r3, #1
	str	r4, [sp, #4]
	mov	r0, r4
	str	r6, [sp]
	mov	r1, #2304
	movs	r2, #3
	movt	r1, 61
	bl	mmap(PLT)
	ldr	r3, .L157+80
	ldr	r10, [fp, r3]
	str	r0, [r10]
	adds	r0, r0, #1
	beq	.L149
	ldr	r3, [sp, #32]
	movs	r1, #26
	ldr	r2, [r3]
	movs	r3, #1
	str	r1, [r2, #4]
	str	r3, [r2]
.L61:
	ldr	r3, [r2]
	ands	r3, r3, #1
	bne	.L61
	str	r3, [sp, #40]
	add	r1, sp, #100
	ldr	r3, .L157+84
	movw	r0, #43691
	ldr	r2, .L157+88
	movw	r4, #35391
.LPIC72:
	add	r3, pc
	str	r3, [sp, #104]
	ldr	r3, .L157+92
.LPIC71:
	add	r2, pc
	str	fp, [sp, #64]
	mov	fp, r10
.LPIC91:
	add	r3, pc
	str	r3, [sp, #80]
	ldr	r3, .L157+96
	mov	r10, r8
	movt	r0, 10922
	movt	r4, 503
.LPIC92:
	add	r3, pc
	str	r1, [sp, #68]
	str	r0, [sp, #72]
	str	r2, [sp, #100]
	str	r4, [sp, #76]
	str	r3, [sp, #84]
.L96:
	ldr	r3, [sp, #36]
	ldr	r2, [r3]
	movs	r3, #4
	str	r3, [r2, #48]
	str	r3, [r2]
.L62:
	ldr	r3, [r2]
	ands	r3, r3, #4
	bne	.L62
	ldr	r2, [sp, #40]
	movs	r0, #1
	str	r3, [sp, #48]
	ldr	r3, [sp, #68]
	ldr	r1, .L157+100
	ldr	r4, [r3, r2, lsl #2]
.LPIC73:
	add	r1, pc
	mov	r2, r4
	bl	__printf_chk(PLT)
	ldr	r1, .L157+104
	mov	r0, r4
.LPIC74:
	add	r1, pc
	bl	fopen(PLT)
	mov	r5, r0
	cmp	r0, #0
	beq	.L150
	ldr	r4, [sp, #48]
	b	.L63
.L64:
	adds	r4, r4, #1
.L63:
	mov	r0, r5
	bl	fgetc(PLT)
	adds	r0, r0, #1
	bne	.L64
	movs	r2, #0
	mov	r0, r5
	mov	r1, r2
	bl	fseek(PLT)
	movs	r1, #1
	mov	r0, r4
	bl	calloc(PLT)
	mov	r3, r5
	mov	r2, r4
	movs	r1, #1
	mov	r9, r0
	bl	fread(PLT)
	cmp	r4, r0
	bhi	.L151
	mov	r0, r5
	bl	fclose(PLT)
	mov	r0, r9
	bl	strlen(PLT)
	ldr	r1, .L157+108
.LPIC77:
	add	r1, pc
	subs	r3, r0, #2
	mov	r8, r0
	movs	r0, #1
	str	r3, [sp, #20]
	mov	r2, r3
	mov	r5, r3
	and	r4, r3, r0
	bl	__printf_chk(PLT)
	ldr	r1, .L157+112
	mvns	r2, r5
	movs	r0, #1
	and	r2, r2, #1
.LPIC78:
	add	r1, pc
	bl	__printf_chk(PLT)
	ldr	r1, [sp, #72]
	asrs	r3, r5, #31
	movs	r2, #12
	smull	r0, r1, r5, r1
	rsb	r3, r3, r1, asr #1
	mls	r2, r2, r3, r5
	cbz	r2, .L66
	adds	r3, r3, #1
.L66:
	movs	r2, #10
	ldr	r1, .L157+116
	mul	r3, r2, r3
	add	r7, sp, #92
	add	r5, sp, #96
.LPIC79:
	add	r1, pc
	movs	r0, #1
	str	r5, [sp, #28]
	mov	r6, r3
	mov	r2, r3
	str	r3, [sp, #44]
	bl	__printf_chk(PLT)
	mov	r2, r6
	mov	r0, r7
	movs	r1, #12
	bl	makeArray(PLT)
	mov	r0, r5
	ldr	r1, [sp, #20]
	movs	r2, #3
	bl	makeArray(PLT)
	ldr	r0, [r7]
	mov	r3, r6
	lsls	r6, r6, #1
	add	r5, r0, #48
	movs	r1, #0
	mov	ip, r6
	mov	r6, r3
.L67:
	cbz	r6, .L72
	ldr	r3, [r0]
	add	r2, ip, r3
.L68:
	strh	r1, [r3], #2	@ movhi
	cmp	r2, r3
	bne	.L68
.L72:
	adds	r0, r0, #4
	cmp	r5, r0
	bne	.L67
	ldr	r3, [sp, #32]
	ldr	lr, [r3]
	ldr	r3, [sp, #20]
	cmp	r3, #0
	ble	.L152
	ldr	r3, [sp, #28]
	sub	ip, r9, #2
	add	ip, ip, r8
	mov	r5, r9
	ldr	r6, [r3]
	subs	r6, r6, #4
.L74:
	ldr	r0, [r6, #4]!
	mov	r1, r5
	subs	r2, r0, #2
	adds	r0, r0, #4
.L73:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	subs	r3, r3, #97
	strh	r3, [r2, #2]!	@ movhi
	cmp	r0, r2
	bne	.L73
	adds	r5, r5, #1
	cmp	ip, r5
	bne	.L74
	movs	r3, #2
	str	r3, [lr]
	ldr	r3, .L157+120
	mov	r9, #0
	ldr	r8, [sp, #28]
	mov	r6, r9
.LPIC80:
	add	r3, pc
	ldr	r2, .L157+124
	str	fp, [sp, #56]
	mov	fp, r6
	str	r10, [sp, #60]
	mov	r10, r3
.LPIC81:
	add	r2, pc
	str	r4, [sp, #52]
	str	r2, [sp, #16]
.L77:
	ldr	r3, [r8]
	mov	r0, r10
	lsl	r4, fp, #1
	ldr	r5, .L157+128
	ldr	r3, [r3, r9, lsl #2]
.LPIC84:
	add	r5, pc
	ldrh	r1, [r3]
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	strh	r0, [r3, fp, lsl #1]	@ movhi
	ldr	r0, [sp, #16]
	bl	assemble(PLT)
	ldr	r2, [r7]
	ldr	r1, [r8]
	ldr	r3, [r2, r6, lsl #2]
	ldr	r1, [r1, r9, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #2]	@ movhi
	mov	r0, r10
	ldrh	r1, [r1]
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #4]	@ movhi
	ldr	r0, .L157+132
.LPIC83:
	add	r0, pc
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #6]	@ movhi
	mov	r0, r5
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #8]	@ movhi
	ldr	r0, [sp, #16]
	bl	assemble(PLT)
	ldr	r2, [r7]
	ldr	r1, [r8]
	ldr	r3, [r2, r6, lsl #2]
	ldr	r1, [r1, r9, lsl #2]
	add	r9, r9, #1
	add	r3, r3, r4
	strh	r0, [r3, #10]	@ movhi
	mov	r0, r10
	ldrh	r1, [r1, #4]
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #12]	@ movhi
	ldr	r0, .L157+136
.LPIC87:
	add	r0, pc
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #14]	@ movhi
	mov	r0, r5
	bl	assemble(PLT)
	ldr	r3, [r7]
	movs	r1, #0
	ldr	r3, [r3, r6, lsl #2]
	add	r3, r3, r4
	strh	r0, [r3, #16]	@ movhi
	ldr	r0, .L157+140
.LPIC89:
	add	r0, pc
	bl	assemble(PLT)
	ldr	r3, [r7]
	adds	r1, r6, #1
	movw	r2, #43691
	movt	r2, 43690
	cmp	r6, #11
	ldr	r3, [r3, r6, lsl #2]
	it	eq
	addeq	fp, fp, #10
	add	r4, r4, r3
	umull	r2, r3, r1, r2
	lsrs	r6, r3, #3
	ldr	r3, [sp, #20]
	cmp	r3, r9
	strh	r0, [r4, #18]	@ movhi
	mov	r0, #12
	mls	r6, r0, r6, r1
	bne	.L77
	ldrd	r4, fp, [sp, #52]
	ldr	r10, [sp, #60]
.L97:
	cmp	r4, #0
	beq	.L153
	movs	r4, #0
.L79:
	ldr	r3, [sp, #44]
	ldr	r2, .L157+32
	cmp	r3, #0
	beq	.L154
	ldr	r0, .L157+144
	ldr	r3, .L157+44
.LPIC93:
	add	r0, pc
	str	r0, [sp, #52]
	ldr	r0, [sp, #64]
	ldr	r1, [sp, #44]
	ldr	r5, [sp, #48]
	ldr	r9, [r0, r2]
	add	r8, r1, #-1
	ldr	r3, [r0, r3]
	str	fp, [sp, #44]
	mov	fp, r1
	str	r9, [sp, #20]
	ldr	r9, [sp, #76]
	str	r3, [sp, #16]
.L92:
	ldr	r1, [r7]
	lsls	r6, r4, #1
	ldr	r3, [r10]
	lsl	lr, r5, #1
	subs	r2, r1, #4
	add	ip, r1, #44
	adds	r1, r3, r6
.L86:
	ldr	r0, [r2, #4]!
	cmp	ip, r2
	ldrh	r0, [r0, lr]
	strh	r0, [r1], #2	@ movhi
	bne	.L86
	add	r2, r3, #128
	add	r1, r6, #24
	add	r2, r2, r6
	add	r3, r3, r1
	movs	r1, #0
.L87:
	strh	r1, [r3], #2	@ movhi
	cmp	r2, r3
	bne	.L87
	add	r3, r4, #64
	cmp	r8, r5
	it	ne
	cmpne	r3, r9
	it	le
	movle	r4, r3
	bgt	.L155
.L88:
	adds	r5, r5, #1
	cmp	fp, r5
	bne	.L92
	ldr	fp, [sp, #44]
	ldr	r9, [sp, #20]
.L85:
	ldr	r0, .L157+148
	movs	r1, #0
	lsls	r5, r4, #1
.LPIC94:
	add	r0, pc
	bl	assemble(PLT)
	ldr	r1, [r10]
	adds	r3, r5, #2
	add	r2, r1, #128
	add	r3, r3, r1
	add	r2, r2, r5
	strh	r0, [r1, r4, lsl #1]	@ movhi
	movs	r1, #0
.L93:
	strh	r1, [r3], #2	@ movhi
	cmp	r2, r3
	bne	.L93
	ldr	r0, [sp, #28]
	movs	r1, #3
	bl	freeArray(PLT)
	mov	r0, r7
	movs	r1, #12
	movs	r5, #128
	bl	freeArray(PLT)
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #36]
	ldr	r0, [r9]
	ldr	r1, [r3]
	add	r3, r4, #64
	ldr	r2, [r2]
	movs	r4, #1
	lsls	r3, r3, r4
	str	r4, [r2]
	str	r0, [r2, #24]
	str	r3, [r2, #40]
	str	r4, [r2, #48]
	str	r1, [r2, #72]
	str	r5, [r2, #88]
.L94:
	ldr	r3, [r2, #52]
	lsls	r3, r3, #19
	bpl	.L94
	movs	r0, #10
	ldr	r4, .L157+152
	bl	putchar(PLT)
	movs	r5, #0
.LPIC95:
	add	r4, pc
.L95:
	ldr	r3, [fp]
	mov	r1, r4
	movs	r0, #1
	ldr	r2, [r3, r5]
	adds	r5, r5, #4
	bl	__printf_chk(PLT)
	cmp	r5, #128
	bne	.L95
	movs	r0, #10
	bl	putchar(PLT)
	ldr	r3, [sp, #32]
	ldr	r4, [sp, #40]
	movs	r2, #0
	ldr	r3, [r3]
	str	r2, [r3]
	cmp	r4, #0
	beq	.L101
	ldr	r0, .L157+156
.LPIC96:
	add	r0, pc
	bl	puts(PLT)
	bl	clock(PLT)
	ldr	r3, [sp, #24]
	vldr.64	d4, .L157
	ldr	r1, .L157+160
	vldr.64	d6, .L157+8
.LPIC97:
	add	r1, pc
	subs	r3, r0, r3
	mov	r0, r4
	vmov	s14, r3	@ int
	vcvt.f64.s32	d7, s14
	vdiv.f64	d5, d7, d4
	vmul.f64	d7, d5, d6
	vmov	r2, r3, d7
	bl	__printf_chk(PLT)
	b	.L53
.L143:
	ldr	r0, .L157+164
.LPIC62:
	add	r0, pc
	bl	perror(PLT)
.L53:
	ldr	r3, [sp, #12]
	movs	r0, #0
	ldr	r2, [sp, #1132]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L156
	addw	sp, sp, #1140
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L142:
	ldr	r0, .L157+168
.LPIC60:
	add	r0, pc
	bl	perror(PLT)
	b	.L53
.L146:
	ldr	r0, .L157+172
.LPIC67:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r8
	bl	close(PLT)
	b	.L53
.L144:
	ldr	r0, .L157+176
.LPIC64:
	add	r0, pc
	bl	perror(PLT)
	b	.L53
.L145:
	ldr	r0, .L157+180
.LPIC66:
	add	r0, pc
	bl	perror(PLT)
	b	.L53
.L101:
	movs	r3, #1
	str	r3, [sp, #40]
	b	.L96
.L153:
	ldr	r6, .L157+184
	mov	r5, r4
.LPIC90:
	add	r6, pc
.L102:
	movs	r1, #26
	mov	r0, r6
	bl	assemble(PLT)
	ldr	r3, [r10]
	strh	r0, [r3]	@ movhi
.L81:
	adds	r4, r4, #1
	beq	.L102
	ldr	r3, [r10]
	cmp	r4, #63
	strh	r5, [r3, r4, lsl #1]	@ movhi
	bne	.L81
	movs	r4, #64
	movs	r6, #0
	b	.L82
.L83:
	ldr	r3, [r10]
	cmp	r4, #128
	strh	r6, [r3, r5]	@ movhi
	beq	.L79
.L82:
	lsls	r5, r4, #1
	adds	r4, r4, #1
	cmp	r4, #65
	bne	.L83
	movs	r1, #0
	ldr	r0, [sp, #80]
	bl	assemble(PLT)
	ldr	r3, [r10]
	strh	r0, [r3, r5]	@ movhi
	b	.L82
.L147:
	ldr	r0, .L157+188
.LPIC68:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r7
	bl	close(PLT)
	b	.L53
.L155:
	ldr	r0, [sp, #84]
	bl	puts(PLT)
	movs	r1, #0
	ldr	r0, [sp, #52]
	bl	assemble(PLT)
	ldr	r1, [r10]
	add	ip, r6, #128
	add	r3, r6, #130
	add	r2, r1, #256
	add	r3, r3, r1
	add	r2, r2, r6
	strh	r0, [r1, ip]	@ movhi
	movs	r1, #0
.L89:
	strh	r1, [r3], #2	@ movhi
	cmp	r2, r3
	bne	.L89
	add	r2, r4, #128
	ldr	r1, [sp, #20]
	ldr	r3, [sp, #36]
	ldr	r4, [sp, #16]
	ldr	r0, [r1]
	movs	r1, #1
	ldr	r3, [r3]
	lsls	r2, r2, r1
	ldr	r4, [r4]
	str	r1, [r3]
	str	r0, [r3, #24]
	movs	r0, #128
	str	r2, [r3, #40]
	str	r1, [r3, #48]
	str	r4, [r3, #72]
	str	r0, [r3, #88]
.L90:
	ldr	r2, [r3, #52]
	lsls	r2, r2, #19
	bpl	.L90
	movs	r2, #4
	str	r2, [r3, #48]
	str	r2, [r3]
.L91:
	ldr	r4, [r3]
	ands	r4, r4, #4
	bne	.L91
	b	.L88
.L148:
	ldr	r0, .L157+192
.LPIC69:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r5
	bl	close(PLT)
	b	.L53
.L154:
	ldr	r1, [sp, #64]
	ldr	r3, .L157+44
	ldr	r9, [r1, r2]
	ldr	r3, [r1, r3]
	str	r3, [sp, #16]
	b	.L85
.L152:
	movs	r3, #2
	str	r3, [lr]
	b	.L97
.L149:
	ldr	r0, .L157+196
.LPIC70:
	add	r0, pc
	bl	perror(PLT)
	mov	r0, r6
	bl	close(PLT)
	b	.L53
.L156:
	bl	__stack_chk_fail(PLT)
.L141:
	ldr	r0, .L157+200
.LPIC57:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L140:
	ldr	r0, .L157+204
.LPIC54:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L151:
	ldr	r0, .L157+208
.LPIC76:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L150:
	ldr	r0, .L157+212
.LPIC75:
	add	r0, pc
	bl	perror(PLT)
	movs	r0, #1
	bl	exit(PLT)
.L158:
	.align	3
.L157:
	.word	0
	.word	1093567616
	.word	0
	.word	1083129856
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC51+4)
	.word	__stack_chk_guard(GOT)
	.word	.LC30-(.LPIC52+4)
	.word	.LC31-(.LPIC53+4)
	.word	src_phys(GOT)
	.word	.LC33-(.LPIC55+4)
	.word	.LC34-(.LPIC56+4)
	.word	dst_phys(GOT)
	.word	.LC33-(.LPIC58+4)
	.word	.LC36-(.LPIC59+4)
	.word	.LC38-(.LPIC61+4)
	.word	.LC40-(.LPIC63+4)
	.word	.LC42-(.LPIC65+4)
	.word	top(GOT)
	.word	dma(GOT)
	.word	src(GOT)
	.word	dst(GOT)
	.word	.LC1-(.LPIC72+4)
	.word	.LC0-(.LPIC71+4)
	.word	.LC6-(.LPIC91+4)
	.word	.LC55-(.LPIC92+4)
	.word	.LC48-(.LPIC73+4)
	.word	.LC49-(.LPIC74+4)
	.word	.LC52-(.LPIC77+4)
	.word	.LC53-(.LPIC78+4)
	.word	.LC54-(.LPIC79+4)
	.word	.LC3-(.LPIC80+4)
	.word	.LC8-(.LPIC81+4)
	.word	.LC5-(.LPIC84+4)
	.word	.LC10-(.LPIC83+4)
	.word	.LC11-(.LPIC87+4)
	.word	.LC6-(.LPIC89+4)
	.word	.LC7-(.LPIC93+4)
	.word	.LC7-(.LPIC94+4)
	.word	.LC56-(.LPIC95+4)
	.word	.LC57-(.LPIC96+4)
	.word	.LC58-(.LPIC97+4)
	.word	.LC39-(.LPIC62+4)
	.word	.LC37-(.LPIC60+4)
	.word	.LC44-(.LPIC67+4)
	.word	.LC41-(.LPIC64+4)
	.word	.LC43-(.LPIC66+4)
	.word	.LC3-(.LPIC90+4)
	.word	.LC45-(.LPIC68+4)
	.word	.LC46-(.LPIC69+4)
	.word	.LC47-(.LPIC70+4)
	.word	.LC35-(.LPIC57+4)
	.word	.LC32-(.LPIC54+4)
	.word	.LC51-(.LPIC76+4)
	.word	.LC50-(.LPIC75+4)
	.size	main, .-main
	.comm	dst_phys,4,4
	.comm	src_phys,4,4
	.comm	dst,4,4
	.comm	src,4,4
	.comm	dma,4,4
	.comm	top,4,4
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	.ascii	"load\000"
	.space	3
.LC4:
	.ascii	"wbitem\000"
	.space	1
.LC5:
	.ascii	"xor\000"
.LC6:
	.ascii	"store\000"
	.space	2
.LC7:
	.ascii	"last\000"
	.space	3
.LC8:
	.ascii	"move\000"
	.space	3
.LC9:
	.ascii	"wb\000"
	.space	1
.LC10:
	.ascii	"rshift1\000"
.LC11:
	.ascii	"rshift2\000"
.LC12:
	.ascii	"rshift4\000"
.LC13:
	.ascii	"rshift8\000"
.LC14:
	.ascii	"rshift16\000"
	.space	3
.LC15:
	.ascii	"rshift32\000"
	.space	3
.LC16:
	.ascii	"rshift64\000"
	.space	3
.LC17:
	.ascii	"rshift128\000"
	.space	2
.LC18:
	.ascii	"rshift256\000"
	.space	2
.LC19:
	.ascii	"rshift512\000"
	.space	2
.LC20:
	.ascii	"lshift1\000"
.LC21:
	.ascii	"lshift2\000"
.LC22:
	.ascii	"lshift4\000"
.LC23:
	.ascii	"lshift8\000"
.LC24:
	.ascii	"lshift16\000"
	.space	3
.LC25:
	.ascii	"lshift32\000"
	.space	3
.LC26:
	.ascii	"lshift64\000"
	.space	3
.LC27:
	.ascii	"lshift128\000"
	.space	2
.LC28:
	.ascii	"lshift256\000"
	.space	2
.LC29:
	.ascii	"error\000"
	.space	2
.LC30:
	.ascii	"\012  -------------------------------------- HDC Pr"
	.ascii	"ogram start ------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC31:
	.ascii	"/sys/class/u-dma-buf/udmabuf0/phys_addr\000"
.LC32:
	.ascii	"  Failed: read /sys/class/u-dma-buf/udmabuf0/phys_a"
	.ascii	"ddr\000"
	.space	1
.LC33:
	.ascii	"%lx\000"
.LC34:
	.ascii	"/sys/class/u-dma-buf/udmabuf1/phys_addr\000"
.LC35:
	.ascii	"  Failed: read /sys/class/u-dma-buf/udmabuf1/phys_a"
	.ascii	"ddr\000"
	.space	1
.LC36:
	.ascii	"/dev/udmabuf0\000"
	.space	2
.LC37:
	.ascii	"  Failed: open /dev/udmabuf0\000"
	.space	3
.LC38:
	.ascii	"/dev/udmabuf1\000"
	.space	2
.LC39:
	.ascii	"  Failed: open /dev/udmabuf1\000"
	.space	3
.LC40:
	.ascii	"/dev/uio0\000"
	.space	2
.LC41:
	.ascii	"  Falied: open /dev/uio0\000"
	.space	3
.LC42:
	.ascii	"/dev/uio1\000"
	.space	2
.LC43:
	.ascii	"  Failed: open /dev/uio1\000"
	.space	3
.LC44:
	.ascii	"  mmap top\000"
	.space	1
.LC45:
	.ascii	"  mmap dma\000"
	.space	1
.LC46:
	.ascii	"  mmap src\000"
	.space	1
.LC47:
	.ascii	"  mmap dst\000"
	.space	1
.LC0:
	.ascii	"data/decorate/en\000"
	.space	3
.LC1:
	.ascii	"data/decorate/fr\000"
	.space	3
.LC48:
	.ascii	"\012------------- %s\343\201\256\345\255\246\347\277"
	.ascii	"\222 -------------\012\012\000"
	.space	1
.LC49:
	.ascii	"r\000"
	.space	2
.LC50:
	.ascii	"  Failed: open file\000"
.LC51:
	.ascii	"  Failed: fread file\000"
	.space	3
.LC52:
	.ascii	"all_ngram: %d\012\000"
	.space	1
.LC53:
	.ascii	"even: %d\012\000"
	.space	2
.LC54:
	.ascii	"all_instruction: %d\012\012\000"
	.space	2
.LC55:
	.ascii	"------------DMA\345\206\215\347\231\272\350\241\214"
	.ascii	"-----------\000"
.LC56:
	.ascii	"%u\012\000"
.LC57:
	.ascii	"\012  --------------------------------------- HDC P"
	.ascii	"rogram end -------------------------------------\012"
	.ascii	"\000"
	.space	2
.LC58:
	.ascii	"\012\012  time %lf[ms]\012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
