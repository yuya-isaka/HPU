test:
	arm-linux-gnueabihf-gcc test_hdc.c -o test_hdc
	arm-linux-gnueabihf-gcc test_hdc_pre.c -o test_hdc_pre
	arm-linux-gnueabihf-gcc test_hdc_next.c -o test_hdc_next

run:
	sudo ./test_hdc

clean:
	rm test_hdc test_hdc_pre test_hdc_next

%: %.c
	arm-linux-gnueabihf-gcc $@.c -o $@