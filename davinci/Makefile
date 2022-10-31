
hdc:
	gcc -Wall -o hdc hdc.c -lm

hdc-o:
	gcc -Wall -O2 -o hdc hdc.c -lm


linux:
	arm-linux-gnueabihf-gcc -Wall -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -o hdc-pl hdc-pl.c -lm

linux-o:
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-pl hdc-pl.c -lm


clean:
	rm -f hdc


.PHONY: clean

test:
	gcc -Wall -o test_hash test_hash.c