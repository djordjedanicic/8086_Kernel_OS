/*
 * semaphor.cpp
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */
#include "semaphor.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init);
	myImpl->setID(++sem_uid);
	arrayKernSem[myImpl->getID()]=myImpl;
}

Semaphore::~Semaphore(){
	delete arrayKernSem[myImpl->getID()];
	arrayKernSem[myImpl->getID()]=0;
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n){
	return myImpl->signal(n);
}

int Semaphore::val() const{
	return myImpl->val();
}


