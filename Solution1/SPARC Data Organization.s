
	/****************************************************************************/
	/**************      Project #10 Junda Yin A48999549  ***********************/
	/****************************************************************************/

	.section ".text"
	.align	4

	.global	insert
	.global search
	.global delete

delete:
	save	%sp, -96, %sp		
	mov	%i0, %l0		!table address
	mov	%i1, %l1		!id number
	lduh	[%l0+2],%l2		!student count

	mov	%l0,%o0
	mov	%l1, %o1
	mov	%sp,%o2

	call	search			!do search
	nop

	mov	%o0,%l3			!move the result from search function
	ld	[%o2],%l4		!student address

	cmp	%l3,0
	be	not1			!student does not exist
	nop

	ld	[%l0+8],%l5		!some bytes calculations and arrangement
	sub	%l4,%l5,%l5		!some bytes calculations and arrangement
	sdiv	%l5,48,%l5		!some bytes calculations and arrangement
	sub	%l2, %l5,%l5		!some bytes calculations and arrangement
	smul	%l5,48,%o2		!some bytes calculations and arrangement

	sub	%l2,1,%l2		!student count -1
	stuh	%l2, [%i0+2]		!table count
	mov	%l4,%o0
	add	%o0, 48,%o1

	call	memmove
	nop

	set	1,%i0			!delete successed
	ret
	restore

not1:
	set	0,%i0
	ret
	restore

	


search:
	save	%sp, -96, %sp

	mov	%i0, %l0		!table address
	mov	%i1, %l1		!id
	lduh	[%i0+2], %l2		!student count
	ld	[%i0+8],%l3		!student
	clr	%l4			!count of loop
	
loop:
	cmp	%l2, %l4		!looked up everything
	ble	notfind
	nop
	ld	[%l3+0], %l5		!id
	cmp	%l5, %l1		!compare to the inpur id
	be	find			!if you fidn someone
	nop
	cmp	%l5, %l1		!compare to the input id
	bg	notfind			!dones't find
	nop
	add	%l3,48,%l3		!next person
	inc	%l4			!increment
	ba	loop			!back to the top of the loop
	nop

notfind:
	set	0, %i0			!failed
	st	%l3, [%i2+0]		!the location where the loop stop
	ba	done1
	nop

find:
	set	1,%i0			!successed
	st	%l3, [%i2+0]		!same as the not find
	ba	done1
	nop
done1:
	ret
	restore


insert:
	save	%sp, -96, %sp

	mov	%i0,%l0			!table address
	mov	%i1,%l1			!id
	lduh	[%l0+0], %l2		!capacity
	lduh	[%l0+2], %l3		!student count

	cmp	%l3,%l2			!full or not
	bge	not2
	nop

	mov	%l0,%o0
	mov	%l1,%o1
	mov	%sp,%o2
	
	call	search
	nop


	mov	%o0, %l4		!result
	ld	[%o2], %l6		!find student address



	cmp	%l4, 1			!if there is such student
	be	not2
	nop

	ld	[%l0+8], %l7		!bytes calculation and arrangement
	sub	%l6, %l7, %l7
	sdiv	%l7, 48, %l7
	sub	%l3, %l7, %l7
	smul	%l7, 48, %o2

	mov	%l6, %o1		!source
	add	%o1, 48, %o0		!destination
	
	
	call	memmove
	nop

	add	%l3,1,%l3		!count ++
	stuh	%l3, [%i0+2]		!table count++

	st	%i1, [%l6+0]		!name
	stuh	%i3, [%l6+40]		!exam 1
	stuh	%i4, [%l6+42]		!exam 2
	stuh	%i4, [%l6+44]		!hw

	add	%l6,4,%o0
	mov	25,%o2
	mov	%i2,%o1
	call	memmove
	nop

	clr	%l5
	add	%i3, %i4, %l5		!total
	add	%l5,%i5, %l5
	st	%l5,[%l6+36]

	mov	%l5,%r17		!put l5 into %r16
	mov	400,%r18		!put 400 into %r17

	st	%r17,[%sp+104]		!convert first value to SP format
	ld	[%sp+104], %f16		!store %r17 into memory, load from
	fitos	%f16, %f24		!memory into %f16, convert in %f24

	st	%r18, [%sp+108]		!convert second argument to SP format
	ld	[%sp+108],%f17		!store %r18 into memory, load from
	fitos	%f17, %f25		!memory into %f17, convert in %f25

	fdivs	%f24,%f25,%f26		!get the average

	st	%f26,[%l6+32]		!store it into memory

	set	1, %i0			!successed
	ret
	restore

not2:
	set	0, %i0			!failed
	ret
	restore
