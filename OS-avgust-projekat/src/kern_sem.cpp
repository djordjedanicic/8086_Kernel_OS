/*
 * kern_sem.cpp
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */
#include "timer.h"
#include "kern_sem.h"


KernelSem::KernelSem(int init) :id(0), blckPCBsOnThisSem(0) {
	val_sem = init;
}

int KernelSem::wait(int maxTimeToWait) {
	if(maxTimeToWait>=0){
		if (maxTimeToWait == 0) {
#ifndef BCC_BLOCK_IGNORE
			lock;
#endif
			if (--val_sem < 0) {
				block();
			}
#ifndef BCC_BLOCK_IGNORE
			unlock;
#endif
			return 1;
		} else {
#ifndef BCC_BLOCK_IGNORE
			lock;
#endif
			if (--val_sem < 0) {
/*#ifndef BCC_BLOCK_IGNORE
				lock;
#endif
				//printf("blokirao sam da spava %d, a lck je = %d\n",maxTimeToWait, lck);
#ifndef BCC_BLOCK_IGNORE
				unlock;
#endif*/
				PCB::running->myThread->sleep(maxTimeToWait);
				block();
				if(PCB::running->wake_up==1){
					blckPCBsOnThisSem->remove(PCB::running->id);
					val_sem++;
					PCB::running->wake_up=0;
#ifndef BCC_BLOCK_IGNORE
					unlock;
#endif
					return 0;
				}
				//onaj fleg koji sluzi da znamo da li je odblokiran zato sto je odspavao resetovati, a pre toga ispitati fleg zbog povratne vrednosti wait-a
			}
#ifndef BCC_BLOCK_IGNORE
			unlock;
#endif
			return 1;
		}
	}else{
		return 1;
	}
}

int KernelSem::signal(int n) {

	if (n >= 0) {
		if (n == 0) { //standardan nacin
#ifndef BCC_BLOCK_IGNORE
			lock;
#endif
/*#ifndef BCC_BLOCK_IGNORE
		lock;
#endif
		printf("---------------\n");
		printf("vrednost semafora pre signala: %d\n",val_sem);
		printf("---------------\n");
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif
#ifndef BCC_BLOCK_IGNORE
							lock;
			#endif
							printf("---------------\n");
							printf("blokiranih ne probudjenih niti u listi: %d\n", blckPCBsOnThisSem->getNumNoWakeUpPCBs());
							printf("---------------\n");

			#ifndef BCC_BLOCK_IGNORE
							unlock;
			#endif*/
			if (val_sem++ < 0) {
				deblock();
			}

/*#ifndef BCC_BLOCK_IGNORE
		lock;
#endif
		printf("---------------\n");
		printf("vrednost semafora nakon signala: %d\n",val_sem);
		printf("---------------\n");
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif*/

#ifndef BCC_BLOCK_IGNORE
			unlock;
#endif
			return 0;
		} else {
#ifndef BCC_BLOCK_IGNORE
			lock;
#endif
/*#ifndef BCC_BLOCK_IGNORE
		lock;
#endif
		printf("---------------\n");
		printf("vrednost semafora pre signala: %d\n",val_sem);
		printf("---------------\n");
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif


			#ifndef BCC_BLOCK_IGNORE
							lock;
			#endif
							printf("------- u listi : %d\n", blckPCBsOnThisSem->getNumNoWakeUpPCBs());
			#ifndef BCC_BLOCK_IGNORE
							unlock;
			#endif*/

			int temp = 0;
			if (blckPCBsOnThisSem != 0) {
				if(blckPCBsOnThisSem->getNumNoWakeUpPCBs()>0){
					if (n < blckPCBsOnThisSem->getNumNoWakeUpPCBs()) {
						for (int i = 0; i < n; i++) {
							deblock();
						}
						temp = n;
					} else {
						int pom = blckPCBsOnThisSem->getNumNoWakeUpPCBs();
						for (int i = 0; i < pom; i++) {
							deblock();
						}
						temp = pom;
					}
					val_sem += n;
				}
			}

/*#ifndef BCC_BLOCK_IGNORE
		lock;
#endif
		printf("---------------\n");
		printf("vrednost semafora nakon signala: %d\n",val_sem);
		printf("---------------\n");
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif*/


#ifndef BCC_BLOCK_IGNORE
			unlock;
#endif
			return temp;
		}
	} else {
		return n;
	}
}

void KernelSem::block() {
	PCB::running->flag = -1;
	if (blckPCBsOnThisSem == 0) {
		blckPCBsOnThisSem = new ListPCB();
	}
	blckPCBsOnThisSem->add(PCB::running);
	dispatch();
}

void KernelSem::deblock() {
	while(blckPCBsOnThisSem->getFirst()->wake_up==1){
		PCB* temp = blckPCBsOnThisSem->get_del_First();
	}
	if (blckPCBsOnThisSem != 0 && blckPCBsOnThisSem->getFirst()) {
		PCB* temp = blckPCBsOnThisSem->get_del_First();
		PCB::listSleep->remove(temp->id);
		temp->flag = 2;
		Scheduler::put(temp);
	}
}

int KernelSem::val() const {
	return val_sem;
}

void KernelSem::setID(int id) {
	this->id = id;
}

int KernelSem::getID() {
	return id;
}

