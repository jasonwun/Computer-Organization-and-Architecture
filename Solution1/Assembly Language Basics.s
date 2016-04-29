
	.global main

	.section ".text"
	.align	4

main:
	save	%sp, -96, %sp

	clr	%r16	!Total number of characters
	clr	%r17	!Number of newline characters
	clr	%r18	!Number of whitespace characters
	clr	%r19	!Number of octal digits
	clr	%r20	!Number of decimal digits
	clr	%r21	!Number of hexadecimal digits
	clr	%r22	!Number of letters

loop:	call	getchar
	nop

	!End the loop if register 8 is -1
	cmp	%r8, -1
	be	end
	nop
	
!Check newline characters	
if1:	
	cmp	%r8, '\n'	!New Line
	bne	endif1
	nop
then1:
	inc	%r17		!Increment for both newline and whitespace
	inc	%r18		!Increment for both newline and whitespace

	
endif1:	


!Check whitespace
if2:
	cmp	%r8,' '		
	bne	endif2
	nop
then2:
	inc	%r18		!Increment if it is white space

endif2:


if3:
	cmp	%r8,'\t'
	bne	endif3
	nop
then3:
	inc	%r18		!Increment if it is tab

endif3:


	!Check octal, basically for the digit comparison
	!the digit from 0 to 7 are Octal, Decimal, Hex
	!Therefore, increment three of them
if4:
	cmp	%r8, '0'
	blt	endif4
	nop
	cmp	%r8,'7'
	bgt	endif4
	nop
then4:
	inc	%r19
	inc	%r20
	inc	%r21

endif4:

	!Check decimal,what makes the digit decimal is the digit bigger
	!than 7 smaller than 9. But also these digits are hex either, so
	!increment both decimal and hex
	
if5:
	cmp	%r8,'8'
	blt	endif5
	nop
	cmp	%r8,'9'
	bgt	endif5
	nop
then5:
	inc	%r20
	inc	%r21

endif5:


	!Check hex, hex contains letters and they also count as letters
	!Increment both hex and letter(capital and lower case)
if6:
	cmp	%r8, 'A'
	blt	endif6
	nop
	cmp	%r8, 'F'
	bgt	endif6
	nop
then6:
	inc	%r21
	inc	%r22
endif6:


if7:
	cmp	%r8, 'a'
	blt	endif7
	nop
	cmp	%r8,'f'
	bgt	endif7
	nop
then7:
	inc	%r21
	inc	%r22


endif7:


	!Check letters, the rest of the characters are letters only no doubt
	
if8:
	cmp	%r8, 'G'
	blt	endif8
	nop
	cmp	%r8, 'Z'
	bgt	endif8
	nop
then8:
	inc	%r22

endif8:


if9:
	cmp	%r8, 'g'
	blt	endif9
	nop
	cmp	%r8, 'z'
	bgt	endif9
	nop
then9:
	inc	%r22

endif9:

	ba	loop
	nop

end:
	set 	fmt1, %r8
	mov	%r16, %r9
	call	printf
	nop

	set 	fmt2, %r8
	mov	%r17, %r9
	call	printf
	nop

	set 	fmt3, %r8
	mov	%r18, %r9
	call	printf
	nop

	set 	fmt4, %r8
	mov	%r19, %r9
	call	printf
	nop

	set 	fmt5, %r8
	mov	%r20, %r9
	call	printf
	nop

	set 	fmt6, %r8
	mov	%r21, %r9
	call	printf
	nop

	set 	fmt7, %r8
	mov	%r22, %r9
	call	printf
	nop
	
	ret
	restore


fmt1:
	.asciz	"\nTotal number of characters: %d\n"

fmt2:
	.asciz	"\nNumber of newline characters: %d\n"

fmt3:
	.asciz	"\nNumber of whitespace characters: %d\n"

fmt4:
	.asciz	"\nNumber of octal digits: %d\n"

fmt5:
	.asciz	"\nNumber of decimal digits: %d\n"

fmt6:
	.asciz	"\nNumber of hexadecimal digits: %d\n"

fmt7:
	.asciz	"\nNumber of letters: %d\n"

