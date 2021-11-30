	.arch msp430g2553
	.p2align 1,0
	.text

	.global led_dim_state_machine
	.extern red_on
	.extern led_changed

led_dim_state_machine:
	cmp r12, #0
	jnz else
	mov #1, red_on
	jmp endif
else:
	call redOneThird
endif:
	mov #1, led_changed
	call led_update
	
