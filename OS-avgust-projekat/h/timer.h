/*
 * timer.h
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_


extern unsigned int lck;


// Zabranjuje prekide
#define lock asm {pushf; cli;};


// Dozvoljava prekide
#define unlock asm{popf;};



#endif /* TIMER_H_ */
