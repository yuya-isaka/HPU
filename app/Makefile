
default:
	arm-linux-gnueabihf-gcc -O2 addr_test.c -o addr_test

check:
	arm-linux-gnueabihf-gcc addr_test.c -Wall -o addr_test

asm:
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o addr_test.s addr_test.c -lm


%: %.c
	arm-linux-gnueabihf-gcc $@.c -o $@


clean:
	rm addr_test

.PHONY: default check asm clean
