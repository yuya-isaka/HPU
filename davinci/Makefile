
default:
	gcc -o hdc hdc.c -lm
	gcc -o hdc-pl-check hdc-pl-check.c -lm
	gcc -o hdc-new hdc-new.c -lm
	gcc -o binding binding.c -lm

check:
	gcc -Wall -O2 -o hdc hdc.c -lm
	gcc -Wall -O2 -o hdc-pl-check hdc-pl-check.c -lm
	gcc -Wall -O2 -o hdc-new hdc-new.c -lm
	gcc -Wall -O2 -o binding binding.c -lm


linux:
	arm-linux-gnueabihf-gcc -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -o hdc-new hdc-new.c -lm
	arm-linux-gnueabihf-gcc -o hdc-pl hdc-pl.c -lm
	arm-linux-gnueabihf-g++ -o hdc-pl-cpp hdc-pl.cpp -lm
	arm-linux-gnueabihf-gcc -o hdc-random hdc-random.c -lm
	arm-linux-gnueabihf-gcc -o hdc-binding hdc-binding.c -lm

linux-check:
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc hdc.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-new hdc-new.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-pl hdc-pl.c -lm
	arm-linux-gnueabihf-g++ -Wall -O2 -o hdc-pl-cpp hdc-pl.cpp -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-random hdc-random.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o hdc-binding hdc-binding.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -o binding binding.c -lm


clean:
	rm -f hdc hdc-pl hdc-pl-cpp hdc-pl-check hdc-new

.PHONY: default check linux linux-check clean
