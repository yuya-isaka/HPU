
hdc: hdc.c
	gcc -Wall -o hdc hdc.c -lm

hdc-o: hdc.c
	gcc -Wall -O2 -o hdc hdc.c -lm

.PHONY: clean
clean:
	rm -f hdc

linux:
	arm-linux-gnueabihf-gcc -Wall -o hdc hdc.c -lm

linux-o:
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc hdc.c -lm
