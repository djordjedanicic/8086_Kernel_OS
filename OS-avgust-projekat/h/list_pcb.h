/*
 * list.h
 *
 *  Created on: Apr 20, 2020
 *      Author: OS1
 */

#ifndef LIST_PCB_H_
#define LIST_PCB_H_
#include <stdio.h>
#include "pcb.h"

class ListPCB{
	struct Elem{
		PCB* t;
		Elem* next;
		Elem(PCB* e): t(e), next(0){}
	};
	Elem *head, *tail;
	int numElem;
public:
	ListPCB():head(0), tail(0),numElem(0){}

	~ListPCB();

	void add(PCB* data);

	int getNumElem();

	PCB* get_del_First();

	PCB* getFirst();

	void remove(int id);

	int getNumNoWakeUpPCBs();

};

#endif /* LIST_PCB_H_ */
