*Program SHB7
*Switches the matrix rows around
N           EQU 4             ; Number of matrix rows
M           EQU 5             ; Number of matrix columns
PORTB	    EQU	$1000
OUTA        EQU $FFB8         ; Address of OUTA Buffalo subroutine
OUTSTRG     EQU $FFC7         ; Address of OUTSTRG Buffalo subroutine
OUTCRLF     EQU $FFC4         ; Address of OUTCRLF Buffalo subroutine
OUT1BSP     EQU $FFBE         ; Address of OUT1BSP Buffalo subroutine
*Declares matricies
	ORG	$00
Data	FCB	$00, $01, $02, $03, $04, $05, $06, $07, $08, $09;10


R	FCB	1
V	FCB	1
	
	ORG	$B600         ; Save code in EPROM
**** START OF MAIN PROGRAM ****
Main    LDS	#$01FF        ; Initialize SP  	20

	LDX 	#MSG1         ; Load X with base address of MSG1
	JSR 	OUTSTRG       ; Call subroutine to print MSG1
	BSR 	DELAY      ;Call subroutine to print original matrix

	LDX 	#MSG2         ; Load X with base address of MSG2
	JSR 	OUTSTRG       ; Call subroutine to print MSG2

	SWI               ; return to Buffalo monitor
**** CODE FOR SUBROUTINES GOES HERE ****
DELAY                 ; code for delaying 1/3 seconds
	PSHA
	PSHB
	LDD	#4600	;run nop loop this many times to get .333 seconds

loop	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP		;18 NOPs to make it 20.5 us per loop
	
	SUBD	#1
	CPD	#0
	BNE	loop
	
	PULA
	PULB
	RTS               ; Return from subroutine
DISPLAY
	
	STX	PORTB
	INX
	
	RTS               ; code for swapping the matrix columns
		              ; Return from subroutine

DISP_DATA
	PSHA
	CLRA
	CLRB
loop2	ldx	#Data
loop3	JSR	DISPLAY
	JSR	DELAY
	INCA
	CMPA	#10
	BNE	loop3
	INCB
	CMPB	#2
	BNE	loop2
	PULA
	PULB
	RTS
	
**** DEFINE MESSAGES ****
MSG1	FCC	"The original matrix is as follows:" 
	FCB	$04
MSG2	FCC	"The modified matrix is as follows:" 
	FCB	$04