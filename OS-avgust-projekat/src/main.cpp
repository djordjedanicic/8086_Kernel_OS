/*
 * main.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: OS1
 */
#include "timer.h"
#include <stdio.h>
#include "thread.h"
#include "semaphor.h"
#include "ivtEntry.h"
#include <dos.h>
#include "event.h"
#include <stdlib.h>
#include <iostream.h>

void inic();
void restore();



int userMain(int argc, char* argv[]);



int main(int argc, char* argv[]){
	inic();


	PCB *main = new PCB(4096,2,0);
	PCB::running = main;

	userMain(argc,argv);


	delete main;


	restore();
	return 0;

}

