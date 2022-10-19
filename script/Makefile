generate:
	python3 fpga-bit-to-bin.py --flip design_1_wrapper.bit output.bin

send:
	scp -r ../app ../script petalinux@192.168.1.24:/home/petalinux/
