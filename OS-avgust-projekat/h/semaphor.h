/*
 * semaphor.h
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include <stdio.h>
#include "kern_sem.h"

typedef unsigned int Time;
static int sem_uid=0;

class KernelSem;

class Semaphore {
public:
	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n=0);
	int val() const; // Returns the current value of the semaphore

	friend class KernelSem;// da li je potrebo????

private:
	KernelSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
