/*
 * list_slp.cpp
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */
#include "timer.h"
#include "list_slp.h"


ListSleep::~ListSleep(){
	Elem* current = head;
	while( current != 0 ) {
		Elem* next = current->next;
		delete current;
		current = next;
	}
	head = 0;
	numElem=0;
}

void ListSleep::add(PCB* data,int time){
	if(head==0){
		head = new Elem(data,time);
	}else{
		Elem* temp = new Elem(data,time);
		Elem *ptr = head;
		Elem *prev = 0;
		int diff_time = time-head->time;
		while(diff_time>0 && ptr->next){
			prev = ptr;
			ptr = ptr->next;
			diff_time -= ptr->time;
		}
		if(diff_time > 0){
			if(ptr->next)
				temp->next = ptr->next->next;
			ptr->next=temp;
			temp->time = diff_time;
		}else{
			if(prev!=0){
				prev->next = temp;
				temp->next = ptr;
				temp->time = diff_time+ptr->time;
				ptr->time -= temp->time;
			}else{
				temp->next = head;
				head->time -= temp->time;
				head = temp;
			}
		}
	}
	numElem++;
}


void ListSleep::decTime(){
	if(head!=0){
		head->time--;
		while(head && head->time == 0){
			//printf("Vreme %d", head->time);
			Elem *temp = head;
			head->pcb->wake_up=1;

			head->pcb->flag=2;
			Scheduler::put(head->pcb);

			head=head->next;
			delete temp;
			numElem--;
		}
	}
}

void ListSleep::remove(int id){
	Elem *ptr = head;
	Elem *prev = 0;
	while(ptr){
		if(ptr->pcb->id==id){
			if(prev!=0){
				if(ptr->next){
					prev->next = ptr->next;
					ptr->next->time += ptr->time;
				}else{
					prev->next = 0;
				}
			}else{
				if(ptr->next){
					ptr->next->time += ptr->time;
					head = ptr->next;
				}else {
					head = 0;
				}
			}
			delete ptr;
			break;
		}
		prev=ptr;
		ptr = ptr->next;
	}
}

int ListSleep::getNumElem(){
	return numElem;
}


