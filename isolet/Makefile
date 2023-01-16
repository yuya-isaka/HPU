test:
	gcc -c -DHV64 -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -DHV64 -O2 -o isolet.o isolet_hv.c
	gcc -DHV64 -O2 -o isolet_bin isolet.o hyper_vector.o
	rm hyper_vector.o isolet.o

check:
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o isolet.o isolet_hv_check.c
	gcc -fopenmp -DOPENMP -DHV64 -O2 -o isolet_bin isolet.o hyper_vector.o
	rm hyper_vector.o isolet.o
	./isolet_bin
	rm isolet_bin

omp:
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o isolet.o isolet_hv.c
	gcc -fopenmp -DOPENMP -DHV64 -O2 -o isolet_bin isolet.o hyper_vector.o
	rm hyper_vector.o isolet.o

generate:
	gcc -DDEBUG -O2 -o isolet_bin isolet_generate.c
	./isolet_bin
	rm isolet_bin

# Petalinux Armv7
linux:
	arm-linux-gnueabihf-gcc -c -O2 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O2 -o isolet_hv.o isolet_hv.c
	arm-linux-gnueabihf-gcc -O2 -o isolet_hv_peta hyper_vector.o isolet_hv.o
	arm-linux-gnueabihf-gcc -c -O2 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O2 -o isolet_hdc.o isolet_hdc.c
	arm-linux-gnueabihf-gcc -O2 -o isolet_hdc hdc_processor.o isolet_hdc.o
	rm hdc_processor.o isolet_hdc.o hyper_vector.o isolet_hv.o

# Petalinux Armv7
peta:
	gcc -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -O2 -o isolet_hv.o isolet_hv.c
	gcc -O2 -o isolet_hv_peta hyper_vector.o isolet_hv.o
	gcc -c -O2 -o hdc_processor.o hdc_processor.c
	gcc -c -O2 -o isolet_hdc.o isolet_hdc.c
	gcc -O2 -o isolet_hdc hdc_processor.o isolet_hdc.o
	rm hdc_processor.o isolet_hdc.o hyper_vector.o isolet_hv.o

clean:
	rm isolet_bin isolet_hv_peta isolet_hdc

.PHONY: test check omp generate linux clean peta