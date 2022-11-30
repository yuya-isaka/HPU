
default:
	gcc -O2 -o davinci_ngram davinci_ngram.c -lm
	./davinci_ngram

new:
	gcc -O2 -o davinci_ngram_new davinci_ngram_new.c -lm
	./davinci_ngram_new

batch:
	gcc -O2 -o davinci_ngram_new_batch davinci_ngram_new_batch.c -lm
	./davinci_ngram_new_batch

# g++ -mavx2 -O2 -o davinci_ngram_intel davinci_ngram_intel.cpp -lm

check:
	gcc -Wall -o davinci_ngram davinci_ngram.c -lm

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
