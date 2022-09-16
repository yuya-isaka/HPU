first:
	sudo mount -t configfs configfs /configfs
	sudo mkdir -p /configfs/device-tree/overlays/full
	cd ~/zynq-test/overlay
	rm pynq_sample.dtbo design_1_wrapper.bit.bin design_1_wrapper.bit
	bootgen -image pynq_sample.bif -arch zynq -process_bitstream bin
	dtc -I dts -O dtb -o pynq_sample.dtbo pynq_sample.dts
	sudo cp -f design_1_wrapper.bit.bin /lib/firmware
	sudo cp pynq_sample.dtbo /configfs/device-tree/overlays/full/dtbo
	sudo sh -c "echo 1 > /configfs/device-tree/overlays/full/status"
	sudo rm /lib/firmware/design_1_wrapper.bit.bin

second:
	sudo sh -c "echo 0 > /configfs/device-tree/overlays/full/status"
	sudo rmdir /configfs/device-tree/overlays/full/
	cd ~/zynq-test/overlay
	rm pynq_sample.dtbo design_1_wrapper.bit.bin design_1_wrapper.bit
	bootgen -image pynq_sample.bif -arch zynq -process_bitstream bin
	dtc -I dts -O dtb -o pynq_sample.dtbo pynq_sample.dts
	sudo cp -f design_1_wrapper.bit.bin /lib/firmware
	sudo cp pynq_sample.dtbo /configfs/device-tree/overlays/full/dtbo
	sudo sh -c "echo 1 > /configfs/device-tree/overlays/full/status"
	sudo rm /lib/firmware/design_1_wrapper.bit.bin
