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
./1mat/mat_ctrl.sv \
./2src/p_ctrl.sv \
./2src/src_ctrl.sv \
./2src/src_en_ctrl.sv \
./2src/s_ctrl.sv \
./3exe/exe_ctrl.sv \
./3exe/out_ctrl.sv \
./4dst/dst_ctrl.sv \
./buf/src_buf.sv \
./buf/dst_buf.sv \
./core/core.sv \
./param/agu.sv \
./param/agu_next.sv \
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
	../bin/iStyle --style=kr -n $(DESIGN_SRCS)

.PHONY:
