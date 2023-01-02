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

.PHONY: test