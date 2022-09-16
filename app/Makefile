all:
	/tools/Xilinx/Vitis/2022.1/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-gcc test.c -o test

send:
	scp ./test petalinux@192.168.1.24:~/

remove:
	ssh-keygen -R 192.168.1.24