VCODE = $(wildcard ./vsrc/top.v)
CCODE = $(wildcard ./csrc/sim_top.cpp)

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
	
include ../Makefile
