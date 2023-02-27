send_all:
	scp -r  ./overlay fpga@192.168.1.29:/home/fpga/
	scp -r  ./app fpga@192.168.1.29:/home/fpga/
	scp -r ./davinci fpga@192.168.1.29:/home/fpga/
	scp -r ./mnist fpga@192.168.1.29:/home/fpga/
	scp -r ./isolet fpga@192.168.1.29:/home/fpga/

send_overlay:
	scp -r  ./overlay fpga@192.168.1.29:/home/fpga/

send_app:
	scp -r  ./app fpga@192.168.1.29:/home/fpga/

send_davinci:
	scp -r ./davinci fpga@192.168.1.29:/home/fpga/

send_mnist:
	scp -r ./mnist fpga@192.168.1.29:/home/fpga/

send_isolet:
	scp -r ./isolet fpga@192.168.1.29:/home/fpga/
