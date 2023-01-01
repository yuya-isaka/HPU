# 32bit実行
check:
	gcc -c -O3 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# 32bit実行デバッグ
debug-check:
	gcc -c -O3 -DDEBUG -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DDEBUG -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# 64bit実行
check64:
	gcc -c -O3 -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# 64bit実行デバッグ
debug-check64:
	gcc -c -O3 -DDEBUG -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DDEBUG -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DDEBUG -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# 32bit並列処理
mac-omp:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# 64bit並列処理
mac-omp64:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -mcpu=apple-m1 -DOPENMP -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -mcpu=apple-m1 -DOPENMP -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Intel 32bit並列処理
intel-omp:
	gcc -fopenmp -c -O3 -DOPENMP -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -c -O3 -DOPENMP -o davinci_ngram.o davinci_ngram.c
	gcc -fopenmp -O3 -DDEBUG -DOPENMP -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Intel 64bit並列処理
intel-omp64:
	gcc -fopenmp -c -O3 -DOPENMP -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -fopenmp -c -O3 -DOPENMP -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -fopenmp -O3 -DDEBUG -DOPENMP -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Mac SIMD 32bit
mac-neon:
	gcc -c -O3 -DSIMD -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DSIMD -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DSIMD -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Mac SIMD 64bit
mac-neon64:
	gcc -c -O3 -DSIMD -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -c -O3 -DSIMD -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -O3 -DSIMD -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Mac SIMD 32bit並列処理
mac-neon-omp:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DOPENMP -DSIMD -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DOPENMP -DSIMD -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DOPENMP -DSIMD -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

# Mac SIMD 64bit並列処理
mac-neon64-omp64:
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DOPENMP -DSIMD -DHV64 -o hyper_vector.o hyper_vector.c
	gcc -I/opt/homebrew/include -Xpreprocessor -fopenmp -c -O3 -DOPENMP -DSIMD -DHV64 -o davinci_ngram.o davinci_ngram.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp -lomp -O3 -DOPENMP -DSIMD -DHV64 -o davinci_ngram davinci_ngram.o hyper_vector.o
	rm hyper_vector.o davinci_ngram.o
	./davinci_ngram

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

.PHONY: check debug-check check64 debug-check64 mac-omp mac-omp64 intel-omp intel-omp64 mac-neon mac-neon64 linux clean