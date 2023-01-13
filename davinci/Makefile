# 64bit実行
test:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o

# 64bit実行デバッグ
debug-test:
	gcc -c -O3 -DDEBUG -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DDEBUG -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o

# 64bit並列処理
omp:
	gcc -fopenmp -c -O3 -DOPENMP -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -c -O3 -DOPENMP -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -fopenmp -O3 -DOPENMP -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o

# Petalinux Armv7
linux:
	arm-linux-gnueabihf-gcc -c -O3 -o hyper_vector.o hyper_vector.c
	arm-linux-gnueabihf-gcc -c -O3 -o davinci_ngram_peta.o davinci_ngram.c
	arm-linux-gnueabihf-gcc -O3 -o davinci_ngram_peta hyper_vector.o davinci_ngram_peta.o
	arm-linux-gnueabihf-gcc -c -O3 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O3 -o ohashi_ngram.o ohashi_ngram.c
	arm-linux-gnueabihf-gcc -O3 -o ohashi_ngram hdc_processor.o ohashi_ngram.o
	rm hdc_processor.o ohashi_ngram.o hyper_vector.o davinci_ngram_peta.o

# remove バイナリ
clean:
	rm -f davinci_ngram davinci_ngram_peta ohashi_ngram

.PHONY: test debug-test omp linux clean