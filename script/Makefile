generate:
	python fpga-bit-to-bin.py --flip design_1_wrapper.bit output.bin

send:
	scp -r ../app ../script petalinux@192.168.1.24:/home/petalinux/

over:
	echo 0 > /sys/class/fpga_manager/fpga0/flags
	cp output.bin /lib/firmware/
	echo output.bin > /sys/class/fpga_manager/fpga0/firmware
