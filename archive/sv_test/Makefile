SHELL = /bin/bash
TARGET_ARCH = linux64

SIM_DIR = sim
VERILATOR = verilator

# verilator_top = new Vsv_test; より
TOP = Vsv_test

VERILATOR_OPTION = \
	-Wall \
	-Wno-WIDTH \
	-Wno-UNUSED \
	-Wno-BLKSEQ \
	--cc \
	+1364-2001ext+v \
	-Wno-fatal \
	--Mdir sim \
	--trace \
	-MAKEFLAGS "OBJCACHE=ccache CXX=clang++ LINK=clang++" \
	--compiler clang \

VERILATOR_MAKE_OPTION = \
	OPT="-O3 -I ../../../" \

DESIGN_SRC = \
./sv_test.sv

VERILATOR_TB = tb_sv_test.cpp

default: $(SIM_DIR)/$(TOP)
	./sim/$(TOP)

$(SIM_DIR)/$(TOP): $(DESIGN_SRC) $(VERILATOR_TB)
	$(VERILATOR) $(VERILATOR_OPTION) $(DESIGN_SRC) --exe ../$(VERILATOR_TB)
	cd sim; make $(VERILATOR_MAKE_OPTION) -f $(TOP).mk Vsv_test__ALL.a
	cd sim; make $(VERILATOR_MAKE_OPTION) -f $(TOP).mk $(TOP)

clean:
	rm -rf sim/ tmp.vcd

format :
	iStyle --style=kr -n $(DESIGN_SRC)

.PHONY: clean format
