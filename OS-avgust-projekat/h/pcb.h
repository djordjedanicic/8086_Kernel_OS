/*
 * pcb.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "thread.h"
#include "DOS.H"
#include "list_pcb.h"
#include "list_slp.h"

class PCB;


static PCB** arrayPCB = new PCB*[200];//ovo je samo privremeno


class Thread;
class ListPCB;
class ListSleep;

class PCB{
public:
	static PCB* running;
	static ListSleep *listSleep;
	ListPCB* blckPCBs;
	unsigned* stack;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	int finished;
	int quant;
	int flag; //(-1) - blocked, (1) - running, (2) - ready
	int wake_up;
	int id;
	Thread* myThread;


	~PCB();

	static void wrapper(Thread* runningThread);
	PCB (StackSize stackSize,Time timeSlice, Thread* myThread);

protected:
	friend class Thread;
};



#endif /* PCB_H_ */
