/*
 * timer.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */
#include "timer.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include <STDIO.H>
#include "idleT.h"


unsigned oldTimerOFF, oldTimerSEG;


unsigned tsp;
unsigned tss;
unsigned tbp;

/*unsigned main_sp;
unsigned main_ss;
unsigned main_bp;*/

extern void tick();

volatile int brojac = 10;
volatile int zahtevana_promena_konteksta = 0;
IdleThread* idleT = new IdleThread(defaultStackSize,defaultTimeSlice);

void interrupt timer(){

	if(!zahtevana_promena_konteksta){
		if(PCB::listSleep!=0){
			//printf("usao u decTime \n");
			PCB::listSleep->decTime();
		}
	}

	if (!zahtevana_promena_konteksta && brojac!=-1) brojac--;
	if (brojac == 0 || zahtevana_promena_konteksta || PCB::running == idleT->getPCB()) {
		//if(lck==0){
			asm {
				mov tbp, bp
				mov tsp, sp
				mov tss, ss
			}

			if(PCB::running!=0){
				PCB::running->sp = tsp;
				PCB::running->ss = tss;
				PCB::running->bp = tbp;

				if(!PCB::running->finished && PCB::running->flag!=-1 && PCB::running!=idleT->getPCB()){
					PCB::running->flag=2;
					Scheduler::put(PCB::running);
				}
			}else{
				/*main_bp=tbp;
				main_ss=tss;
				main_sp=tsp;*/
			}
			PCB::running = Scheduler::get();

			if(PCB::running!=0){
				PCB::running->flag=1;

				tsp = PCB::running->sp;
				tss = PCB::running->ss;
				tbp = PCB::running->bp;

				brojac = PCB::running->quant;
			}else{
				PCB::running=idleT->getPCB();

				tsp = PCB::running->sp;
				tss = PCB::running->ss;
				tbp = PCB::running->bp;
				brojac = PCB::running->quant;
				/*tbp=main_bp;
				tss=main_ss;
				tsp=main_sp;*/
			}
			asm {
				mov bp, tbp
				mov sp, tsp   // restore sp
				mov ss, tss
			}
		//}
	}

	 // poziv stare prekidne rutine koja se
     // nalazila na 08h, a sad je na 60h
     // poziva se samo kada nije zahtevana promena
     // konteksta – tako se da se stara
     // rutina poziva samo kada je stvarno doslo do prekida
	if(!zahtevana_promena_konteksta){
		tick();
		asm int 60h;
	}

	zahtevana_promena_konteksta = 0;
}

void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}




