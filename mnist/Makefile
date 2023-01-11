test:
	gcc -c -DDEBUG -O3 -o hyper_vector.o hyper_vector.c
	gcc -c -DDEBUG -O3 -o mnist.o mnist_hv.c
	gcc -DDEBUG -O3 -o mnist mnist.o hyper_vector.o
	rm hyper_vector.o mnist.o
	./mnist
	rm mnist

default:
	gcc -DDEBUG -O3 -o mnist mnist.c
	./mnist
	rm mnist

generate:
	gcc -c -DDEBUG -O3 -o hyper_vector.o hyper_vector.c
	gcc -c -DDEBUG -O3 -o mnist.o mnist_data_generate.c
	gcc -DDEBUG -O3 -o mnist mnist.o hyper_vector.o
	rm hyper_vector.o mnist.o
	./mnist
	rm mnist


# Petalinux Armv7
linux:
	arm-linux-gnueabihf-gcc -c -O3 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O3 -o mnist_hv.o mnist_hv.c
	arm-linux-gnueabihf-gcc -O3 -o mnist_hv_peta hyper_vector.o mnist_hv.o
	arm-linux-gnueabihf-gcc -c -O3 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O3 -o mnist_hdc.o mnist_hdc.c
	arm-linux-gnueabihf-gcc -O3 -o mnist_hdc hdc_processor.o mnist_hdc.o
	rm hdc_processor.o mnist_hdc.o hyper_vector.o mnist_hv.o

clean:
	rm mnist_hv_peta mnist_hdc

.PHONY: test