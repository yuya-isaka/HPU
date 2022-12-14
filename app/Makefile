
default:
	arm-linux-gnueabihf-gcc -c -O2 -o  hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O2 -o addr_test.o addr_test.c
	arm-linux-gnueabihf-gcc -O2 -o addr_test hyper_vector.o addr_test.o
	rm hyper_vector.o addr_test.o

check:
	arm-linux-gnueabihf-gcc addr_test.c -Wall -o addr_test

asm:
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o addr_test.s addr_test.c -lm


%: %.c
	arm-linux-gnueabihf-gcc $@.c -o $@


clean:
	rm addr_test

.PHONY: default check asm clean
