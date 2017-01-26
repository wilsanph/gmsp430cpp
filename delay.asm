
;===================
; delay_us(us)
;===================
		; the register R12 has the parameter us
		.global delay_us
delay_us
loop	dec.w 	r12
		jnz		loop
		nop
		.end

;===================
; delay_ms(ms)
;===================
		; the register R12 has the parameter ms
		.global delay_ms
delay_ms
loop	dec.w 	r12
		jnz		loop
		nop
		.end