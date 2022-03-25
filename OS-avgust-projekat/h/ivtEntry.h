/*
 * ivtEntry.h
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include <dos.h>

typedef void interrupt (*pInterrupt)(...);

typedef unsigned char IVTNo;

class KernelEv;

class IVTEntry{
public:
	IVTEntry(IVTNo ivtNo, pInterrupt _newInterruptRoutine);
	~IVTEntry();

	void setEvent(KernelEv* event);
	static IVTEntry* getIVTEntry(IVTNo _ivtNo);

	void signal();
	void callOld();

private:
	static IVTEntry* entries[256];
	IVTNo ivtNo;
	pInterrupt newInterruptRoutine;
	pInterrupt oldInterruptRoutine;
	KernelEv* myEvent;

};





#endif /* IVTENTRY_H_ */
