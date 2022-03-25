/*
 * thread.h
 *
 *  Created on: Mar 29, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <stdio.h>
#include <dos.h>
#include "SCHEDULE.H"




typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

static ID uid=0;


class IdleThread;
class PCB;

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);

	void sleep(int time);


	int finished();

protected:
	friend class PCB;
	friend class IdleThread;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
	ID id;
};


void dispatch();


#endif /* THREAD_H_ */

