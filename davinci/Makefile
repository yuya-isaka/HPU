
default:
	gcc -c -O3 -DDEBUG -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DDEBUG -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

check64:
	gcc -c -O3 -DDEBUG -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DDEBUG -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

omp:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DDEBUG -DOPENMP -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

omp64:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DDEBUG -DOPENMP -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# -ftree-vectorizeをつけても-O3と変わらない
# -O2と-O3では4秒ほど差がある

neon:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DDEBUG -DOPENMP -DSIMD -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

neon64:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DDEBUG -DOPENMP -DSIMD -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

neon2:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -o hyper_vector_neon.o hyper_vector_neon.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DDEBUG -DOPENMP -DSIMD -o davinci_ngram_neon.o davinci_ngram_neon.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DDEBUG -DOPENMP -DSIMD -o davinci_ngram_neon davinci_ngram_neon.o hyper_vector_neon.o
	rm hyper_vector_neon.o davinci_ngram_neon.o
	./davinci_ngram_neon

# g++ -mavx2 -O2 -o davinci_ngram_intel davinci_ngram_intel.cpp -lm

# check:
# 	gcc -Wall -o davinci_ngram davinci_ngram.c -lm

asm:
	gcc -Wall -O2 -S -o davinci_ngram.s davinci_ngram.c -lm



linux:
	arm-linux-gnueabihf-gcc -O2 -o davinci_ngram_peta davinci_ngram.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_ngram ohashi_ngram.c -lm

linux-check:
	arm-linux-gnueabihf-gcc -Wall -o davinci_ngram_peta davinci_ngram.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_ngram ohashi_ngram.c -lm

linux-asm:
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o davinci_ngram_peta.s davinci_ngram.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_ngram.s ohashi_ngram.c -lm



clean:
	rm -f davinci_ngram davinci_ngram_peta ohashi_ngram

.PHONY: default check asm linux linux-check linux-asm clean
