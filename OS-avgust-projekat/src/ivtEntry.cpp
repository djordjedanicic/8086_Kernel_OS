/*
 * ivtEntry.cpp
 *
 *  Created on: Jul 2, 2020
 *      Author: OS1
 */

#include "ivtEntry.h"
#include "kernelEv.h"
#include <dos.h>
#include "timer.h"

IVTEntry* IVTEntry::entries[256]={0};


IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt _newInterruptRoutine){
	entries[ivtNo] = this;
	this->ivtNo = ivtNo;
	myEvent = 0;
	newInterruptRoutine = _newInterruptRoutine;
#ifndef BCC_BLOCK_IGNORE
	lock;
	oldInterruptRoutine = getvect(ivtNo);
	setvect(ivtNo, newInterruptRoutine);
	unlock;
#endif
}

IVTEntry::~IVTEntry(){
	entries[ivtNo] = 0;
	myEvent = 0;
#ifndef BCC_BLOCK_IGNORE
	lock;
	setvect(ivtNo, oldInterruptRoutine);
	unlock;
#endif
	newInterruptRoutine = 0;
	oldInterruptRoutine = 0;
}

void IVTEntry::setEvent(KernelEv* event){
	myEvent = event;
}

IVTEntry* IVTEntry::getIVTEntry(IVTNo _ivtNo){
	return entries[_ivtNo];
}

void IVTEntry::signal(){
	if(myEvent)
		myEvent->signal();
}

void IVTEntry::callOld(){
	oldInterruptRoutine();
}
