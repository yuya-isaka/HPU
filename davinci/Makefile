
default:
	gcc -Wall -o hdc hdc.c -lm
	gcc -Wall -o hdc-xorshift hdc-xorshift.c -lm
	gcc -Wall -o hdc-pl-2 hdc-pl-2.c -lm

check:
	gcc -Wall -O2 -o hdc hdc.c -lm
	gcc -Wall -O2 -o hdc-xorshift hdc-xorshift.c -lm


linux:
	arm-linux-gnueabihf-gcc -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -o hdc-pl hdc-pl.c -lm
	arm-linux-gnueabihf-g++ -o hdc-pl-cpp hdc-pl.cpp -lm

linux-check:
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-pl hdc-pl.c -lm
	arm-linux-gnueabihf-g++ -Wall -O2 -o hdc-pl-cpp hdc-pl.cpp -lm


clean:
	rm -f hdc hdc-pl hdc-pl-cpp

.PHONY: default check linux linux-check clean
