	.arch msp430g2553
	.p2align 1,0
	.text

	.global led_dim_state_machine
	.extern red_on
	.extern led_changed
state:
	.word 0x00
	
jt:
	.word case_0
	.word case_1

led_dim_state_machine:
	mov #1, r12
	cmp &state, r12
	jc end_case
	mov &state, r12
	add r12, r12
	mov jt(r12), pc

case_0:
	mov #1, red_on
	jmp end_case
case_1:
	call redOneThird
	jmp end_case
end_case:
	mov #1, led_changed
	call led_update
	pop pc
	
