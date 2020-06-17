* PROGRAM TO COMPUTE THE SUM OF ALL ODD NUMBERS IN AN ARRAY
* WITH 10 8-BIT ELEMENTS. THE ARRAY IS STORED AT $00-$09. 
* SAVE THE SUM AT MEMORY LOCATION $20-$21.
* THE INDEX REGISTER X IS USED AS THE POINTER TO THE ARRAY ELEMENT.
N       EQU     10
	ORG     $00
ARRAY   FCB     11, 13, 54, 34, 67, 97, 71, 87, 63, 51; ARRAY ELEMENTS
	ORG     $20
SUM     RMB     2
	ORG     $B600
	LDAA    #$00
	STAA    SUM     ; INITIALIZE SUM TO 0
	STAA    SUM+1   ;       �
	LDX     #ARRAY  ; POINT X TO ARRAY[0]
LOOP    BRCLR   0,X $01 CHKEND  ; IS IT AN ODD NUMBER?
	LDD     SUM     ; ADD THE ODD NUMBER TO THE SUM
	ADDB    0,X     ;       �
	ADCA    #0      ;       �
	STD     SUM     ;       �
CHKEND  CPX     #ARRAY+N-1     ; ARE WE AT END OF ARRAY?
	BHS     EXIT    ; IF YES, EXIT
	INX            ; IF NO, CHECK NEXT ELEMENT
	BRA     LOOP    ; 
EXIT    SWI






Annotations