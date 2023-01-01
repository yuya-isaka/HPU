bind:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o bind.o bind.c
	gcc -O3 -DHV64 -o bind_bin bind.o hyper_vector.o
	rm hyper_vector.o bind.o
	./bind_bin
	rm bind_bin

perm:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o perm.o perm.c
	gcc -O3 -DHV64 -o perm_bin perm.o hyper_vector.o
	rm hyper_vector.o perm.o
	./perm_bin
	rm perm_bin

bound:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o bound.o bound.c
	gcc -O3 -DHV64 -o bound_bin bound.o hyper_vector.o
	rm hyper_vector.o bound.o
	./bound_bin
	rm bound_bin

random:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o random.o random.c
	gcc -O3 -DHV64 -o random_bin random.o hyper_vector.o
	rm hyper_vector.o random.o
	./random_bin
	rm random_bin

bind_bound:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o bind_bound.o bind_bound.c
	gcc -O3 -DHV64 -o bind_bound_bin bind_bound.o hyper_vector.o
	rm hyper_vector.o bind_bound.o
	./bind_bound_bin
	rm bind_bound_bin

perm_bound:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o perm_bound.o perm_bound.c
	gcc -O3 -DHV64 -o perm_bound_bin perm_bound.o hyper_vector.o
	rm hyper_vector.o perm_bound.o
	./perm_bound_bin
	rm perm_bound_bin

linux:
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o bind.o bind.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o bind_peta bind.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o perm.o perm.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o perm_peta perm.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o bound.o bound.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o bound_peta bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o random.o random.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o random_peta random.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o bind_bound.o bind_bound.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o bind_bound_peta bind_bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -DHV64 -o perm_bound.o perm_bound.c
	arm-linux-gnueabihf-gcc -O3 -DHV64 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

clean:
	rm -f bind_peta perm_peta bound_peta random_peta bind_bound_peta perm_bound_peta

.PHONY: bind perm bound random bind_bound perm_bound linux clean