#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"

//#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env){
	if(false && argc && argv && env) {}
	Vtop* top = new Vtop;
	
	// the next for rows used to save wave files as VCD files
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	top->trace(m_trace, 5);                 // 5 means the deep of trace
	m_trace->open("waveform.vcd");
	
	// next is simulate code
	while(!Verilated::gotFinish()){
		int a = rand() & 1;
		int b = rand() & 1;
		top->a = a;
		top->b = b;
		top->eval();
		printf("a = %d, b = %d, f = %d\n", a, b, top->f);
		assert(top->f == (a ^ b));		
		m_trace->dump(sim_time);   // write all signals traced into waves
		sim_time++;
	}

	m_trace->close();
	top->final();
	delete top;
	return 0;
}

