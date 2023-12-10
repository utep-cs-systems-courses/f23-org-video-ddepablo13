	.arch msp430g2553
	.p2align 1,0
	.text

	.global switch_interrupt_handler
	.extern switch_update_interrupt_sense
	.extern maze_done
	.extern move_player

switch_interrupt_handler:
	call #switch_update_interrupt_sense
	xor.b #255, r12
	and.b #15, r12
	call #move_player
	pop r0
