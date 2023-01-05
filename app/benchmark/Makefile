default:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o bind.o bind.c
	gcc -O3 -DHV64 -o bind bind.o hyper_vector.o
	gcc -c -O3 -DHV64 -o perm.o perm.c
	gcc -O3 -DHV64 -o perm perm.o hyper_vector.o
	gcc -c -O3 -DHV64 -o bound.o bound.c
	gcc -O3 -DHV64 -o bound bound.o hyper_vector.o
	gcc -c -O3 -DHV64 -o random.o random.c
	gcc -O3 -DHV64 -o random random.o hyper_vector.o
	gcc -c -O3 -DHV64 -o bind_bound.o bind_bound.c
	gcc -O3 -DHV64 -o bind_bound bind_bound.o hyper_vector.o
	gcc -c -O3 -DHV64 -o perm_bound.o perm_bound.c
	gcc -O3 -DHV64 -o perm_bound perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

intel-omp:
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o bind.o bind.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o bind bind.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o perm.o perm.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o perm perm.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o bound.o bound.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o bound bound.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o random.o random.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o random random.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o bind_bound.o bind_bound.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o bind_bound bind_bound.o hyper_vector.o
	gcc -fopenmp -DOPENMP -c -O3 -DHV64 -o perm_bound.o perm_bound.c
	gcc -fopenmp -DOPENMP -O3 -DHV64 -o perm_bound perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

omp:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o bind.o bind.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -o bind bind.o hyper_vector.o
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o perm.o perm.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -o perm perm.o hyper_vector.o
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o bound.o bound.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -o bound bound.o hyper_vector.o
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o random.o random.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -o random random.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o

linux:
	arm-linux-gnueabihf-gcc -c -O3 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O3 -o bind.o bind.c
	arm-linux-gnueabihf-gcc -O3 -o bind_peta bind.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -o perm.o perm.c
	arm-linux-gnueabihf-gcc -O3 -o perm_peta perm.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -o bound.o bound.c
	arm-linux-gnueabihf-gcc -O3 -o bound_peta bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -o random.o random.c
	arm-linux-gnueabihf-gcc -O3 -o random_peta random.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -o bind_bound.o bind_bound.c
	arm-linux-gnueabihf-gcc -O3 -o bind_bound_peta bind_bound.o hyper_vector.o
	arm-linux-gnueabihf-gcc -c -O3 -o perm_bound.o perm_bound.c
	arm-linux-gnueabihf-gcc -O3 -o perm_bound_peta perm_bound.o hyper_vector.o
	rm hyper_vector.o bind.o perm.o bound.o random.o bind_bound.o perm_bound.o

clean:
	rm -f bind_peta perm_peta bound_peta random_peta bind_bound_peta perm_bound_peta bind perm bound random bind_bound perm_bound

.PHONY: default omp linux clean