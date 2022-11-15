SHELL = /bin/bash
TARGET_ARCH = linux64

SIM_DIR = sim
VERILATOR = verilator

# verilator_top = new Vtop; より
TOP = Vtop

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
./top.v \
./main/get_enable.sv \
./main/stream_ctrl.sv \
./main/buffer_ctrl.sv \
./main/core.sv \
./kit/counter.sv \
./kit/xorshift.sv \
./kit/selector.sv \
./kit/agu.sv \

VERILATOR_TB = tb.cpp

default: $(SIM_DIR)/$(TOP)
	./sim/$(TOP)

$(SIM_DIR)/$(TOP): $(DESIGN_SRC) $(VERILATOR_TB)
	$(VERILATOR) $(VERILATOR_OPTION) $(DESIGN_SRC) --exe ../$(VERILATOR_TB)
	cd sim; make $(VERILATOR_MAKE_OPTION) -f $(TOP).mk Vtop__ALL.a
	cd sim; make $(VERILATOR_MAKE_OPTION) -f $(TOP).mk $(TOP)

clean:
	rm -rf sim/ tmp.vcd

format :
	iStyle --style=kr -n -s4 --pad=paren $(DESIGN_SRC)

test:
	g++ test.cpp -o test
	./test
	rm test

.PHONY: clean format test
