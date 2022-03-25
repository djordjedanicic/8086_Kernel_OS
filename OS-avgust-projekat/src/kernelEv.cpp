/*
 * kernelEv.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#include "kernelEv.h"
#include "ivtEntry.h"

KernelEv::KernelEv(IVTNo ivtNo){
	owner = PCB::running;
	this->ivtNo = ivtNo;
	if(IVTEntry::getIVTEntry(ivtNo)){
		IVTEntry::getIVTEntry(ivtNo)->setEvent(this);
	}
}

KernelEv::~KernelEv(){
	IVTEntry::getIVTEntry(ivtNo)->setEvent(0);
}

void KernelEv::wait(){
	if(owner == PCB::running){
		PCB::running->flag = -1;
		dispatch();
	}
}


void KernelEv::signal(){
	if (owner->flag == -1){
		owner->flag = 2;
		Scheduler::put(owner);
	}
}
