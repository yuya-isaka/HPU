%: %.c
	riscv32-unknown-linux-gnu-gcc -march=rv32id -c -o start.o start.S
	riscv32-unknown-linux-gnu-gcc -march=rv32id -c -o $@.o $<
	riscv32-unknown-linux-gnu-ld $@.o start.o -L/opt/riscv32/riscv32-unknown-linux-gnu/lib/ -T link.ld -static -o $@.elf
	riscv32-unknown-linux-gnu-objdump -d $@.elf > $@.dump
	riscv32-unknown-linux-gnu-objcopy -O binary $@.elf $@.bin
	od -An -tx4 -w4 -v $@.bin > $@.hex
	rm -f start.o
	rm -f $@.o
	rm -f $@.elf
	rm -f $@
	rm -f $@.bin

clean:
	$(RM) *.o *.elf *.bin