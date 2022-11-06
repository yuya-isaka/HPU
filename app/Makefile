default:
	arm-linux-gnueabihf-gcc test_hdc.c -o test_hdc

check:
	arm-linux-gnueabihf-gcc -Wall -O2 test_hdc.c -o test_hdc

%: %.c
	arm-linux-gnueabihf-gcc $@.c -o $@

clean:
	rm test_hdc test_hdc-no-reset

.PHONY: default check clean
