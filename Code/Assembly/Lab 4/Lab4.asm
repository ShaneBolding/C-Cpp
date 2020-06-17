*Program SHB7
*Checks Array of N bytes to see if entries are +, -, even, or odd
*Declares flag counters
	ORG	$00
Ne	RMB 1
P	RMB 1
E	RMB 1
O	RMB 1
*Declares Array
	ORG	$100
N	equ	5
array	fcb	N
*Start program
	ORG	$B600
	ldx	#array
Odd	brclr	0,X,$01,Even
	inc	O
	bra	Pos
Even	inc	E
Pos	brclr	0,X,%10000000,Neg
	inc	P
	bra	chkend
Neg	inc	Ne
chkend	cpx	#array+N-1
	bhs	exit
	inx
	bra	Odd	
*End Program
exit	swi
	