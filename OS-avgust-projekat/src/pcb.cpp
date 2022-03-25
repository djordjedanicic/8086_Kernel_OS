/*
 * pcb.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */
#include "timer.h"
#include "DOS.H"
#include "thread.h"
#include "pcb.h"


PCB* PCB::running = 0;
ListSleep* PCB::listSleep=0;

PCB::PCB (StackSize stackSize ,Time timeSlice, Thread* my_Thread) : flag(0), id(0), sp(0), ss(0), blckPCBs(0), wake_up(0){
	myThread = my_Thread;
	stackSize /= sizeof(unsigned);
	if(stackSize>=32768){
		stackSize=2048;
	}
	stack = new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 1] = FP_SEG(my_Thread);
	stack[stackSize - 2] = FP_OFF(my_Thread);


	stack[stackSize - 5] = 0x200;

	stack[stackSize - 6] = FP_SEG(wrapper);
	stack[stackSize - 7] = FP_OFF(wrapper);


	ss = FP_SEG(stack + stackSize - 16);
	sp = FP_OFF(stack + stackSize - 16);
#endif
	bp = sp;

	finished = 0;
	if(timeSlice == 0)
		quant = -1;//vremenski nije ogranicen
	else
		quant = timeSlice;
}


PCB::~PCB(){
	if(blckPCBs!=0){
		delete blckPCBs;
	}
	delete stack;
}


void PCB::wrapper(Thread * runningThread){
	runningThread->run();

	if(runningThread->myPCB->blckPCBs!=0){
		while(runningThread->myPCB->blckPCBs->getFirst()!=0){
			PCB* temp = runningThread->myPCB->blckPCBs->get_del_First();
			temp->flag=2;
			Scheduler::put(temp);
		}
	}
	runningThread->myPCB->finished=1;
	dispatch();
}






