/*
 * kern_sem.h
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */

#ifndef KERN_SEM_H_
#define KERN_SEM_H_
#include <stdio.h>
#include "list_pcb.h"
#include "semaphor.h"


class KernelSem;

static KernelSem** arrayKernSem= new KernelSem*[50];


// proveriti sta sve ide u public a sta u protected i private
class KernelSem{
public:
	//~KernelSem();
	int wait(int maxTimeToWait);
	int signal(int n=0);
	int val() const;

	void block();
	void deblock();

	void setID(int id);
	int getID();
	KernelSem(int init);


	ListPCB* blckPCBsOnThisSem;
private:
	int val_sem;
	int id;

};




#endif /* KERN_SEM_H_ */
