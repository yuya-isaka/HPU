generate:
	python3 fpga-bit-to-bin.py --flip design_1_wrapper.bit output.bin

script:
	scp -r ../script petalinux@192.168.1.24:/home/petalinux/

app:
	scp -r  ../app petalinux@192.168.1.24:/home/petalinux/

davinci:
	scp -r ../davinci petalinux@192.168.1.24:/home/petalinux/

cp:
	cp ../vivado_prj_2/zynq-test-ZC706.runs/impl_1/design_1_wrapper.bit ~/zynq-test/script

.PHONY: generate script app davinci cp