%: %.c
	riscv32-unknown-elf-gcc -march=rv32id -c -o start.o start.S
	riscv32-unknown-elf-gcc -march=rv32id -c -o $@.o $<
	riscv32-unknown-elf-ld $@.o start.o -T link.ld -static -o $@.elf
	riscv32-unknown-elf-objdump -d $@.elf > $@.dump
	riscv32-unknown-elf-objcopy -O binary $@.elf $@.bin
	od -An -tx4 -w4 -v $@.bin > $@.hex
	rm -f start.o
	rm -f $@.o
	rm -f $@.elf
	rm -f $@
	rm -f $@.bin

clean:
	$(RM) *.o *.elf *.bin