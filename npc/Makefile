VCODE = $(wildcard ./vsrc/top.v)
CCODE = $(wildcard ./csrc/sim_vcd.cpp)

ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	$(VERILATOR) -cc --exe --build -j $(VCODE) $(CCODE) --trace
	make -C obj_dir -f Vtop.mk Vtop
	
include ../Makefile
