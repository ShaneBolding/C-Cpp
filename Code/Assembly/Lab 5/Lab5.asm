*Program SHB7
*Switches the matrix rows around
N           EQU 4             ; Number of matrix rows
M           EQU 5             ; Number of matrix columns
OUTA        EQU $FFB8         ; Address of OUTA Buffalo subroutine
OUTSTRG     EQU $FFC7         ; Address of OUTSTRG Buffalo subroutine
OUTCRLF     EQU $FFC4         ; Address of OUTCRLF Buffalo subroutine
OUT1BSP     EQU $FFBE         ; Address of OUT1BSP Buffalo subroutine
*Declares matricies
	ORG	$00
Mat	FCB	$01, $02, $03, $04, $05;10
	FCB	$06, $07, $08, $09, $0A
	FCB	$0B, $0C, $0D, $0E, $0F
	FCB	$10, $11, $12, $13, $14

R	FCB	1
V	FCB	1
	
	ORG	$B600         ; Save code in EPROM
**** START OF MAIN PROGRAM ****
Main    LDS	#$01FF        ; Initialize SP  	20

	LDX 	#MSG1         ; Load X with base address of MSG1
	JSR 	OUTSTRG       ; Call subroutine to print MSG1
	BSR 	PRINTMAT      ;Call subroutine to print original matrix
	BSR 	SWAPMAT       ; Call subroutine to swap matrix columns

	LDX 	#MSG2         ; Load X with base address of MSG2
	JSR 	OUTSTRG       ; Call subroutine to print MSG2

	BSR 	PRINTMAT      ;Call subroutine to print modified matrix  30
	SWI               ; return to Buffalo monitor
**** CODE FOR SUBROUTINES GOES HERE ****
PRINTMAT                 ; code for printing the matrix
	clra
loop	clrb
	JSR	OUT1BSP
	incb
	CMPB	M-1
	BNE	loop
	JSR	OUTCRLF	;	40
	inca
	CMPA	N-1
	BNE	loop

	RTS               ; Return from subroutine
SWAPMAT
	LDX	#Mat
	LDAA	N
	STAA	R	;	50
	LDAA	M	;	
	DECA
	STAA	V
RowLoop	
ColoumnLoop
	LDAA	V,X
	PSHA
	DEC	V
	LDAA	V
	TSTA
	BNE	ColoumnLoop		; 60
	LDAA	M
Restart		;		
	INX
	INC	V
	TSTA
	BNE	Restart
	DEC	V
	DEC	R
	LDAA	R
	TSTA
	BNE	RowLoop
	
	LDAA	M
	LDAA	N
	MUL

	LDX	#Mat
Store
	PULA
	STAA	0,X
	INX
	DECB
	TSTB
	BNE	Store

	RTS               ; code for swapping the matrix columns
		              ; Return from subroutine
**** DEFINE MESSAGES ****
MSG1	FCC	"The original matrix is as follows:" 
	FCB	$04
MSG2	FCC	"The modified matrix is as follows:" 
	FCB	$04
