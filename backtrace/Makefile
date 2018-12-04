all: bt

bt: bt.c retaddress.s backtrack.s
	gcc -g bt.c retaddress.s backtrack.s -o bt


clean:
	rm -rf *.o
	rm bt