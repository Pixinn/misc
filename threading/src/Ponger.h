#ifndef PONGER_H_
#define PONGER_H_

#include "AThread.h"

class Pinger;
class message_from_ping;

//! Type of message sent from Pong
class message_from_pong {
public: int number;
};

//Test class
class Ponger : public AThread {
public:
	I_AM_A_THREAD;
	Ponger();
	void process(const message_from_ping& message);
	Pinger* recipient;
private:
	unsigned _count = 0u;
};

#endif
