default:
	arm-linux-gnueabihf-gcc -c -O2 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O2 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O2 -o addr_test.o addr_test.c
	arm-linux-gnueabihf-gcc -O2 -o addr_test hdc_processor.o hyper_vector.o addr_test.o
	rm hdc_processor.o hyper_vector.o addr_test.o

peta:
	gcc -c -O2 -o hdc_processor.o hdc_processor.c
	gcc -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -O2 -o addr_test.o addr_test.c
	gcc -O2 -o addr_test hdc_processor.o hyper_vector.o addr_test.o
	rm hdc_processor.o hyper_vector.o addr_test.o

%: %.c
	arm-linux-gnueabihf-gcc $@.c -o $@

clean:
	rm addr_test

.PHONY: default clean peta