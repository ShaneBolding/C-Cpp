* Finds the max element of an array and stores it at memory location $20

N	EQU	10	;Array Count

	ORG	$00
Array	FCB	3,24,15,74,4,10,13,12,9,28

	ORG	$100
	LDAA	Array	;sets Array[0] as the temp array max
	LDAB	#1	;initializesws loop index to 1
Loop	LDX	#Array	;poaints x to Array[0]
	ABX		;computes the addres of Array[1]
	CMPA	0,X	;compares the temp array max to the next element
	BHS	CHKEND	;sees if we need to update the temporary array max
	LDAA	0,X	;updates the temperary array max
CHKEND	CMPB	#N-1	;compares the loop index with the loop limit
	BEQ	EXIT	;checks to see if the whole array is checked
	INCB		;increments the loop index
	BRA	Loop	
EXIT	STAA	$220	;saves the array max
	SWI		;terminates the program