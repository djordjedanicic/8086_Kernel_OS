/*
 * event.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#include "event.h"
#include "kernelEv.h"


Event::Event(IVTNo ivtNo){
	myImpl = new KernelEv(ivtNo);
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	if (myImpl){
		myImpl->wait();
	}
}

void Event::signal(){
	if (myImpl){
		myImpl->signal();
	}
}


