/*
 * list_pcb.cpp
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */

#include "list_pcb.h"



ListPCB::~ListPCB(){
	Elem* current = head;
	while(current != 0) {
		Elem* next = current->next;
		delete current;
		current = next;
	}
	head = 0;
	tail=0;
	numElem=0;
}

void ListPCB::add(PCB* data){
	if(head==0){
		head = new Elem(data);
		tail = head;
	}else{
		Elem* temp = new Elem(data);
		tail->next = temp;
		tail = tail->next;
	}
	numElem++;
}

PCB* ListPCB::get_del_First(){
	if(head==0) return 0;
	PCB* t = head->t;
	Elem* temp = head;
	head = head->next;
	if(!head) tail=head;
	delete temp;
	numElem--;
	return t;
}


PCB* ListPCB::getFirst(){
	if(head==0) return 0;
	return head->t;
}

int ListPCB::getNumElem(){
	return numElem;
}

void ListPCB::remove(int id){
	Elem *ptr = head;
	Elem *prev = 0;
	while(ptr){
		if(ptr->t->id==id){
			if(prev!=0){
				if(ptr->next){
					prev->next = ptr->next;
				}else{
					prev->next = 0;
				}
			}else{
				if(ptr->next){
					head = ptr->next;
				}else {
					head = 0;
				}
			}
			delete ptr;
			//return 1;
			break;
		}
		prev=ptr;
		ptr = ptr->next;
	}
	//return 0;
}


int ListPCB::getNumNoWakeUpPCBs(){
	Elem *ptr = head;
	int cnt = 0;
	while(ptr){
		if(ptr->t->wake_up==0){
			cnt++;
		}
		ptr=ptr->next;
	}
	return cnt;
}
