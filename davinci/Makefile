
check:
	gcc -Wall -o hdc hdc.c -lm
	gcc -Wall -o hdc-pl-2 hdc-pl-2.c -lm

hdc-o:
	gcc -Wall -O2 -o hdc hdc.c -lm


linux:
	arm-linux-gnueabihf-gcc -Wall -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -o hdc-pl hdc-pl.c -lm

linux-o:
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-pl hdc-pl.c -lm


clean:
	rm -f hdc hdc-pl hdc-pl-2


.PHONY: clean

test:
	gcc -Wall -o test_hash test_hash.c