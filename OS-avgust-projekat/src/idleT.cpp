/*
 * idleT.cpp
 *
 *  Created on: May 5, 2020
 *      Author: OS1
 */

#include "idleT.h"

void IdleThread::run(){
	while(1);
}

PCB* IdleThread::getPCB(){
	return myPCB;
}
