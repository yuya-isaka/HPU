
hdc: hdc.c
	gcc -Wall -O2 -o hdc hdc.c -lm

.PHONY: clean
clean:
	rm -f hdc

linux:
	arm-linux-gnueabihf-gcc hdc.c -o hdc -lm
