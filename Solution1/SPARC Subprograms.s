
	.section ".text"
	.align	4
	.global	is_infinity
	.global	is_nan
	.global	is_zero
	.global	is_denormal
	.global	negate
	.global	absolute
	.global	classify

is_infinity:
	save	%sp, -96, %sp

	clr	%l0
	clr	%l1
	
	mov	%i0,%l0
	mov	%i0,%l1
	
	sll	%l0,1,%l0
	srl	%l0,21,%l0

	sll	%l1,16,%l1
	srl	%l1,16,%l1

if1:	
	cmp	%l0,(0x7ff)
	bne	then1
	nop

	cmp	%l1, (0x0)
	bne	then1
	nop

	cmp	%i1,(0x0)
	bne	then1
	nop
	
	clr	%i0
	inc	%i0
	ba	endif1
	nop

then1:
	clr	%i0

endif1:
	ret
	restore


is_nan:
	save	%sp, -96, %sp
	nop

	clr	%l0
	clr	%l1

	mov	%i0,%l0
	mov	%i0,%l1
	
	sll	%l0,1,%l0
	srl	%l0,21,%l0

	sll	%l1,16,%l1

if2:	
	cmp	%l0,(0x7ff)
	bne	then2
	nop

	cmp	%l1, (0x0)
	beq	then2i1
	nop


	clr	%i0
	inc	%i0
	ba	endif2
	nop

then2i1:

	cmp	%i1,(0x0)
	beq	then2
	nop

	clr	%i0
	inc	%i0
	ba	endif2
	nop

then2:
	clr	%i0
	

endif2:	
	ret
	restore
	




is_zero:
	save	%sp, -96, %sp

if3:
	cmp	%i0,(0x0)
	bne	then3
	nop

	cmp	%i1,(0x0)
	bne	then3
	nop

	clr	%i0
	inc	%i0


	ba	endif3
	nop

then3:
	clr	%i0

endif3:	
	ret
	restore




is_denormal:
	save	%sp, -96, %sp
	nop

	mov	%i0,%l0
	mov	%i0,%l1
	
	sll	%l0,1,%l0
	sll	%l1,16,%l1
if4:
	cmp	%l0,(0x0)
	bne	then4
	nop

	cmp	%l1,(0x0)
	beq	then4adv
	nop

	clr	%i0
	inc	%i0
	ba	endif4
	nop

then4adv:
	cmp	%i1,(0x0)
	beq	then4
	nop

	clr	%i0
	inc	%i0
	ba	endif4
	nop

then4:
	clr	%i0

endif4:
	ret
	restore

negate:
	save	%sp,-96,%sp

	set	(0x80000000), %l0
	xor	%i0,%l0,%l0
	std	%l0,[%i2]
	ret
	restore



absolute:
	save	%sp,-96,%sp

	set	(0x7fffffff),%l0
	and	%i0,%l0,%l0
	std	%l0,[%i2]

	ret
	restore


classify:
	save	%sp, -96, %sp
	mov	%i0, %l0
	mov	%l0, %o0
	mov	%i1,%l1
	mov	%l1,%o1

	call	is_infinity
	nop
	set	Infinite, %l3
	cmp	%o0, 1
	beq	loop
	nop


	mov	%l0, %o0
	mov	%l1, %o1
	call	is_nan
	nop
	set	NAN, %l3
	cmp	%o0, 1
	beq	loop
	nop

	mov	%l0,%o0
	mov	%l1,%o1
	call	is_zero
	nop
	set	zero, %l3
	cmp	%o0,1
	beq	loop
	nop


	mov	%l0,%o0
	mov	%l1,%o1
	call	is_denormal
	nop
	set	Denormal, %l3
	cmp	%o0,1
	beq	loop
	nop



	set	Normal,%l3
	ba	loop
	nop


loop:
	ldub	[%l3], %l2
	stb	%l2,[%l2]
	cmp	%l2,'\0'
	be	end
	nop

end:
	ret
	restore


zero:		.asciz	"Zero"
NAN:		.asciz	"Not a number"
Infinite:	.asciz	"Infinite"
Denormal:	.asciz	"Denormal"
Normal:		.asciz	"Normal"
