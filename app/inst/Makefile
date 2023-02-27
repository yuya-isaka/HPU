# こっちのほうが良かった
# -O2のほうが良かった
default:
	arm-linux-gnueabihf-gcc -c -O2 -o hdc_processor.o hdc_processor.c
	arm-linux-gnueabihf-gcc -c -O2 -o one.o one.c
	arm-linux-gnueabihf-gcc -O2 -o one hdc_processor.o one.o
	arm-linux-gnueabihf-gcc -c -O2 -o two.o two.c
	arm-linux-gnueabihf-gcc -O2 -o two hdc_processor.o two.o
	arm-linux-gnueabihf-gcc -c -O2 -o four.o four.c
	arm-linux-gnueabihf-gcc -O2 -o four hdc_processor.o four.o
	arm-linux-gnueabihf-gcc -c -O2 -o eight.o eight.c
	arm-linux-gnueabihf-gcc -O2 -o eight hdc_processor.o eight.o
	rm hdc_processor.o one.o two.o four.o eight.o

peta:
	gcc -c -O2 -o hdc_processor.o hdc_processor.c
	gcc -c -O2 -o one.o one.c
	gcc -O2 -o one hdc_processor.o one.o
	gcc -c -O2 -o two.o two.c
	gcc -O2 -o two hdc_processor.o two.o
	gcc -c -O2 -o four.o four.c
	gcc -O2 -o four hdc_processor.o four.o
	gcc -c -O2 -o eight.o eight.c
	gcc -O2 -o eight hdc_processor.o eight.o
	rm hdc_processor.o one.o two.o four.o eight.o

clean:
	rm -rf one two four eight

.PHONY: default clean peta