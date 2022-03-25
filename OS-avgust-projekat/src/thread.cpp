/*
 * thread.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: OS1
 */
//#include "thread.h"
#include "timer.h"
#include "thread.h"
#include "pcb.h"


extern int zahtevana_promena_konteksta;

void interrupt timer();

Thread::Thread (StackSize stackSize, Time timeSlice ){
	myPCB = new PCB(stackSize, timeSlice, this);
	id = ++uid;
	myPCB->id = id;
	arrayPCB[id]=myPCB;

}

Thread::~Thread(){

	waitToComplete();

	delete arrayPCB[id];//kako ga brise?? kao pcb ili pokazivac na pcb(*pcb)
	arrayPCB[id]=0;

}

void Thread::start(){
	if(myPCB->flag==0){
		myPCB->flag=2;
		Scheduler::put(myPCB);
	}

}

void Thread::waitToComplete(){
	if(!myPCB->finished){// da li je mozda bolje while???
		if(myPCB->blckPCBs==0){
			myPCB->blckPCBs = new ListPCB();
		}
		PCB::running->flag=-1;
		myPCB->blckPCBs->add(PCB::running);
		dispatch();
	}
}

void Thread::sleep(int time){
	if(PCB::listSleep==0){
		PCB::listSleep = new ListSleep();
	}
	PCB::listSleep->add(PCB::running,time);
}



void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	lock;
	zahtevana_promena_konteksta = 1;
	timer();
	unlock;
#endif
}


ID Thread::getId(){
	return id;
}
ID Thread::getRunningId(){
	return PCB::running->id;
}
Thread* Thread::getThreadById(ID id){
	return arrayPCB[id]->myThread;
}

int Thread::finished(){
	return myPCB->finished;
}
