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
./sv_test.sv

VERILATOR_CPP_TB = tb_sv_test.cpp

default: $(SIM_DIR)/Vtop
	./sim/Vsv_test

sim: $(SIM_DIR)/Vtop

$(SIM_DIR)/Vtop: $(DESIGN_SRCS) $(VERILATOR_CPP_TB)
	$(VERILATOR) $(VERILATOR_OPTS) $(DESIGN_SRCS) --exe ../$(VERILATOR_CPP_TB)
	cd sim; make $(VERILATOR_MAKE_OPTS) -f Vsv_test.mk Vsv_test__ALL.a
	cd sim; make $(VERILATOR_MAKE_OPTS) -f Vsv_test.mk Vsv_test

clean:
	rm -rf sim/ tmp.vcd

run :
	./sim/Vsv_test

format :
	iStyle --style=kr -n $(DESIGN_SRCS)

.PHONY:
