.global backtrack

backtrack:
	jmp start
start:
	movq (%rbp), %rbp
	jmp exit
exit:
	ret