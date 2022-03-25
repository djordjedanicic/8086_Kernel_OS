/*
 * list_slp.h
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#ifndef LIST_SLP_H_
#define LIST_SLP_H_

#include <stdio.h>
#include "pcb.h"



class ListSleep{
	struct Elem{
		PCB* pcb;
		int time;
		Elem* next;
		Elem(PCB* e, int k): pcb(e), time(k), next(0){}
	};
	Elem *head;
	int numElem;
public:
	ListSleep():head(0), numElem(0){}

	~ListSleep();

	void add(PCB* data, int time);

	void decTime();

	void remove(int id);

	int getNumElem();

	/*PCB* get_del_First();

	PCB* getFirst();*/

};


#endif /* LIST_SLP_H_ */
