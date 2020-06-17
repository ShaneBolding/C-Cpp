*Program SHB&
*Multiplies 3byte by a 1byte
*Declares variables
	ORG	$00
M	RMB 3
N	RMB 1
P	RMB 4
P1	RMB 2
P2	RMB 2
P3	RMB 2
*load A and B with LSB of both Multiplicand and Multiplier
	LDAA	$02
	LDAB	$03
*Multiplies A and B and stores in D
	MUL
*Store B into LSB of Product
	STAB	$07
*Store A into MSB of P1
	STAA	P1
*load the middle byte of Multiplicand to A
	LDAA	$01
*load multiplier into B
	LDAB	$03
*Multiply A and B and store into D
	MUL
*Store D into P2
	STD	P2
*Read MSB of Multiplicand to A
	LDAA	$00
*Multiplier to B
	LDAB	$03
*multiply and store into P3
	MUL
	STD	P3
*Load MSB of P1 into A
	LDAA	P1
*Load LSB of P2 into B
	LDAB	P2+1
*Add A and B into mid byte low of product
	ABA
	STAA	$06
*Put MSB of P2 into A
	LDAA	P2
*Add with carry P3 LSB with A
	ADCA	P3+1
*Store sum into mid byte high of product
	STAA	$05
*P3 MSB to A
	LDAA	P3
*Add w/ carry zero
	ADCA	0
*Store sum to product MSB
	STAA	$04
	