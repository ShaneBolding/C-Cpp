OUT1BSP	EQU	$FFBE ;

	ORG	$00
COUNTER	FCB     10

        ORG	$B600 ;

        LDS     #$01FF        ;
        LDD     $0500        ;

MAIN    PSHA            ;    PUSH A INTO STACK
        PSHB            ;    PUSH B INTO STACK
        PSHA            ;    "           "
        PSHB            ;    "           "
        BSR     PRIME         ;    FIND IF PRIME
        PULA            ;    PULL A FROM STACK
        PULB            ;    "    B               "
        INCB            ;    ADD 1 TO B FOR NEXT NUMBER CHECK
        ADCA    #$00         ;    ADD CARRY
        DEC     COUNTER     ;    DECREASE COUNTER
        BNE     MAIN        ;    BRANCH BACK IF NOT EQUAL TO 0
        SWI            ;


PRIME   PULA        ;    PULL A FROM STACK TO BEGIN PRIME CHECKING
        PULX        ;    PULL X FROM STACK 
        PSHA        ;    PUSH A INTO STACK
        PSHX        ;    PUSH X INTO STACK
        PULX        ;
        PSHX
LOOP    DEX        ;    DECREASE POINTER
        PULA        ;
        PULB        ;
        PSHA        ;
        PSHB        ;
        PSHX        ;
        IDIV        ;    PERFORM DIVISION CHECK
        PULX        ;
        TSTB        ;    TEST B
        BNE     FINISH     ;    BRANCH TO LAST SUBROUTINE UNTIL 0
        TSTA        ;    TEST A
        RTS    ;

FINISH	CPX	#$0002     ;    COMPARE X WITH VALUE STORED IN MEMORY LOCATION 2
        BNE     LOOP     ;
        PULA        ;
        JSR     OUTA     ;
        PULA        ;
        JSR     OUTA     ;