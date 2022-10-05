SHELL = /bin/bash

SIM_DIR = sim

TARGET_ARCH = linux64
VERILATOR   = verilator

VERILATOR_OPTS = \
	-Wall \
	-Wno-WIDTH \
	-Wno-UNUSED \
	-Wno-BLKSEQ \
	--cc \
	+1364-2001ext+v \
	-Wno-fatal \
	--Mdir sim \
	--trace \

VERILATOR_MAKE_OPTS = OPT="-O3 -I ../../../"

DESIGN_SRCS = \
./top.v \
./2src/src_ctrl.sv \
./2src/s_ctrl.sv \
./3exe/exe_ctrl.sv \
./4dst/dst_ctrl.sv \
./buf/dst_buf.sv \
./core/core.sv \
./util/agu.sv \
./util/agu_next.sv \
./util/counter.sv \
./util/xorshift.sv \
# ./param/agu_param.sv \

VERILATOR_CPP_TB = tb.cpp

default: $(SIM_DIR)/Vtop
	./sim/Vtop

sim: $(SIM_DIR)/Vtop

$(SIM_DIR)/Vtop: $(DESIGN_SRCS) $(VERILATOR_CPP_TB)
	$(VERILATOR) $(VERILATOR_OPTS) $(DESIGN_SRCS) --exe ../$(VERILATOR_CPP_TB)
	cd sim; make $(VERILATOR_MAKE_OPTS) -f Vtop.mk Vtop__ALL.a
	cd sim; make $(VERILATOR_MAKE_OPTS) -f Vtop.mk Vtop

clean:
	rm -rf sim/ tmp.vcd

run :
	./sim/Vtop

format :
	iStyle --style=kr -n $(DESIGN_SRCS)

test: test.cpp
	g++ test.cpp -o test
	./test
	rm test

.PHONY:
