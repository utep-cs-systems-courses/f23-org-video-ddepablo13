	.arch msp430g2553
	.p2align 1,0
	.text

	.extern P2REN
	.extern P2IE
	.extern P2OUT
	.extern P2DIR
	.extern switch_update_interrupt_sense
	.global switch_init

switch_init:
	bis.b #15, &P2REN
	bis.b #15, &P2IE
	bis.b #15, &P2OUT
	and.b #240, &P2DIR

	call #switch_update_interrupt_sense
	ret
