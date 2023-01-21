test:
	gcc -c -O2 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O2 -DHV64 -o bind.o bind.c
	gcc -O2 -DHV64 -o bind bind.o hyper_vector.o
	gcc -c -O2 -DHV64 -o perm.o perm.c
	gcc -O2 -DHV64 -o perm perm.o hyper_vector.o
	gcc -c -O2 -DHV64 -o bound.o bound.c
	gcc -O2 -DHV64 -o bound bound.o hyper_vector.o
	gcc -c -O2 -DHV64 -o random.o random.c
	gcc -O2 -DHV64 -o random random.o hyper_vector.o
	gcc -c -O2 -DHV64 -o bind_bound.o bind_bound.c
	gcc -O2 -DHV64 -o bind_bound bind_bound.o hyper_vector.o
	gcc -c -O2 -DHV64 -o perm_bound.o perm_bound.c
	gcc -O2 -DHV64 -o perm_bound perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

omp:
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o bind.o bind.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o bind bind.o hyper_vector.o
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o perm.o perm.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o perm perm.o hyper_vector.o
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o bound.o bound.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o bound bound.o hyper_vector.o
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o random.o random.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o random random.o hyper_vector.o
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o bind_bound.o bind_bound.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o bind_bound bind_bound.o hyper_vector.o
	gcc -fopenmp -c -O2 -DOPENMP -DHV64 -o perm_bound.o perm_bound.c
	gcc -fopenmp -O2 -DOPENMP -DHV64 -o perm_bound perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

linux:
	arm-linux-gnueabihf-gcc -c -O2 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O2 -o bind.o bind.c
	arm-linux-gnueabihf-gcc -O2 -o bind_peta bind.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O2 -o perm.o perm.c
	arm-linux-gnueabihf-gcc -O2 -o perm_peta perm.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O2 -o bound.o bound.c
	arm-linux-gnueabihf-gcc -O2 -o bound_peta bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O2 -o random.o random.c
	arm-linux-gnueabihf-gcc -O2 -o random_peta random.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O2 -o bind_bound.o bind_bound.c
	arm-linux-gnueabihf-gcc -O2 -o bind_bound_peta bind_bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O2 -o perm_bound.o perm_bound.c
	arm-linux-gnueabihf-gcc -O2 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

linux-omp:
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o bind.o bind.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o bind_peta bind.o hyper_vector.o
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o perm.o perm.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o perm_peta perm.o hyper_vector.o
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o bound.o bound.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o bound_peta bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o random.o random.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o random_peta random.o hyper_vector.o
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o bind_bound.o bind_bound.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o bind_bound_peta bind_bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -c -O2 -o perm_bound.o perm_bound.c
	arm-linux-gnueabihf-gcc -fopenmp -DOPENMP -O2 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

peta:
	gcc -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -c -O2 -o bind.o bind.c
	gcc -O2 -o bind_peta bind.o hyper_vector.o
	gcc -c -O2 -o perm.o perm.c
	gcc -O2 -o perm_peta perm.o hyper_vector.o
	gcc -c -O2 -o bound.o bound.c
	gcc -O2 -o bound_peta bound.o hyper_vector.o
	gcc -c -O2 -o random.o random.c
	gcc -O2 -o random_peta random.o hyper_vector.o
	gcc -c -O2 -o bind_bound.o bind_bound.c
	gcc -O2 -o bind_bound_peta bind_bound.o hyper_vector.o
	gcc -c -O2 -o perm_bound.o perm_bound.c
	gcc -O2 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

peta-omp:
	gcc -fopenmp -DOPENMP -c -O2 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -O2 -o bind.o bind.c
	gcc -fopenmp -DOPENMP -O2 -o bind_peta bind.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O2 -o perm.o perm.c
	gcc -fopenmp -DOPENMP -O2 -o perm_peta perm.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O2 -o bound.o bound.c
	gcc -fopenmp -DOPENMP -O2 -o bound_peta bound.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O2 -o random.o random.c
	gcc -fopenmp -DOPENMP -O2 -o random_peta random.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O2 -o bind_bound.o bind_bound.c
	gcc -fopenmp -DOPENMP -O2 -o bind_bound_peta bind_bound.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O2 -o perm_bound.o perm_bound.c
	gcc -fopenmp -DOPENMP -O2 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

clean:
	rm -f bind_peta perm_peta bound_peta random_peta bind_bound_peta perm_bound_peta bind perm bound random bind_bound perm_bound

.PHONY: test omp linux clean