test:
	verilator --cc --exe  --trace-fst --trace-params --trace-structs --trace-underscore top.sv -exe tb_hotate.cpp
	make -C obj_dir -f Vtop.mk
	./obj_dir/Vtop

check:
	verilator -cc top.sv

lint:
	verilator --lint-only -Wall top.sv

push:
	git add .
	git commit -m "$(M)"
	git push origin master

clean:
	rm -rf ./obj_dir
