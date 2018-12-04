.global retaddress

retaddress:
	jmp start
start:
	mov %rbp, %r10
	mov %rbp, %r11
	add $0x8, %r11
	mov (%r11), %rax
	jmp exit
exit:
	ret