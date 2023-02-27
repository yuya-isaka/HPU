test:
	gcc -c -DHV64 -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -DHV64 -O2 -o mnist.o mnist_hv.c
	gcc -DHV64 -O2 -o mnist_bin mnist.o hyper_vector.o
	rm hyper_vector.o mnist.o

omp:
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -DHV64 -O2 -o mnist.o mnist_hv.c
	gcc -fopenmp -DOPENMP -DHV64 -O2 -o mnist_bin mnist.o hyper_vector.o
	rm hyper_vector.o mnist.o

inference:
	gcc -fopenmp -DOPENMP -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -O2 -o mnist.o mnist_hv_inference.c
	gcc -fopenmp -DOPENMP -O2 -o mnist_bin mnist.o hyper_vector.o
	rm hyper_vector.o mnist.o

generate:
	gcc -DDEBUG -O2 -o mnist_bin mnist_data_generate.c
	./mnist_bin
	rm mnist_bin

# Petalinux Armv7
linux:
	arm-linux-gnueabihf-gcc -c -O2 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O2 -o mnist_hv.o mnist_hv.c
	arm-linux-gnueabihf-gcc -O2 -o mnist_hv_peta hyper_vector.o mnist_hv.o
	arm-linux-gnueabihf-gcc -c -O2 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O2 -o mnist_hdc.o mnist_hdc.c
	arm-linux-gnueabihf-gcc -O2 -o mnist_hdc hdc_processor.o mnist_hdc.o
	rm hdc_processor.o mnist_hdc.o hyper_vector.o mnist_hv.o

# Petalinux Armv7
peta:
	gcc -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -O2 -o mnist_hv.o mnist_hv.c
	gcc -O2 -o mnist_hv_peta hyper_vector.o mnist_hv.o
	gcc -c -O2 -o hdc_processor.o hdc_processor.c
	gcc -c -O2 -o mnist_hdc.o mnist_hdc.c
	gcc -O2 -o mnist_hdc hdc_processor.o mnist_hdc.o
	rm hdc_processor.o mnist_hdc.o hyper_vector.o mnist_hv.o

clean:
	rm mnist_hv_peta mnist_hdc

.PHONY: test omp generate linux clean peta