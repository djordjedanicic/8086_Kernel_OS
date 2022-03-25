/*
 * kernelEv.h
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */
#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "pcb.h"
#include "event.h"


class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
private:
	PCB* owner;
	IVTNo ivtNo;
};


#endif /* KERNELEV_H_ */
