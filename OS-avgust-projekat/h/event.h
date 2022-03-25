/*
 * event.h
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "ivtEntry.h"


typedef unsigned char IVTNo;

class KernelEv;

class Event{
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();

protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};


#define PREPAREENTRY(numEntry, _callOld) \
	void interrupt inter##numEntry(...); \
	IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
	void interrupt inter##numEntry(...) { \
		newEntry##numEntry.signal(); \
		if (_callOld) \
			newEntry##numEntry.callOld(); \
	}

#endif /* EVENT_H_ */
