/*
 * idleT.h
 *
 *  Created on: May 5, 2020
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include "thread.h"





class IdleThread : public Thread{
public:
	IdleThread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(stackSize,timeSlice){}
	virtual ~IdleThread(){}
	PCB* getPCB();
protected:
	virtual void run();
};



#endif /* IDLET_H_ */
