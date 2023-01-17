# こっちのほうが良かった
# -O2のほうが良かった
default:
	arm-linux-gnueabihf-gcc -c -O2 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_bind.o ohashi_bind.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bind hdc_processor.o ohashi_bind.o
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_perm.o ohashi_perm.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_perm hdc_processor.o ohashi_perm.o
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_bound.o ohashi_bound.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bound hdc_processor.o ohashi_bound.o
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_perm_bound.o ohashi_perm_bound.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_perm_bound hdc_processor.o ohashi_perm_bound.o
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_bind_bound.o ohashi_bind_bound.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bind_bound hdc_processor.o ohashi_bind_bound.o
	arm-linux-gnueabihf-gcc -c -O2 -o ohashi_random.o ohashi_random.c
	arm-linux-gnueabihf-gcc -O2 -o ohashi_random hdc_processor.o ohashi_random.o
	rm hdc_processor.o ohashi_bind.o ohashi_perm.o ohashi_bound.o ohashi_bind_bound.o ohashi_perm_bound.o ohashi_random.o

peta:
	gcc -c -O2 -o hdc_processor.o hdc_processor.c
	gcc -c -O2 -o ohashi_bind.o ohashi_bind.c
	gcc -O2 -o ohashi_bind hdc_processor.o ohashi_bind.o
	gcc -c -O2 -o ohashi_perm.o ohashi_perm.c
	gcc -O2 -o ohashi_perm hdc_processor.o ohashi_perm.o
	gcc -c -O2 -o ohashi_bound.o ohashi_bound.c
	gcc -O2 -o ohashi_bound hdc_processor.o ohashi_bound.o
	gcc -c -O2 -o ohashi_perm_bound.o ohashi_perm_bound.c
	gcc -O2 -o ohashi_perm_bound hdc_processor.o ohashi_perm_bound.o
	gcc -c -O2 -o ohashi_bind_bound.o ohashi_bind_bound.c
	gcc -O2 -o ohashi_bind_bound hdc_processor.o ohashi_bind_bound.o
	gcc -c -O2 -o ohashi_random.o ohashi_random.c
	gcc -O2 -o ohashi_random hdc_processor.o ohashi_random.o
	rm hdc_processor.o ohashi_bind.o ohashi_perm.o ohashi_bound.o ohashi_bind_bound.o ohashi_perm_bound.o ohashi_random.o

clean:
	rm -f ohashi_random ohashi_perm ohashi_perm_bound ohashi_bind ohashi_bind_bound ohashi_bound

.PHONY: default clean peta