generate:
	python3 fpga-bit-to-bin.py --flip design_1_wrapper.bit output.bin

send:
	scp -r ../app ../script petalinux@192.168.1.24:/home/petalinux/

copy:
	cp ../vivado_prj_2/zynq-test-ZC706.runs/impl_1/design_1_wrapper.bit ~/zynq-test/script
