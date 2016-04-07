#ifndef PINGER_H_
#define PINGER_H_

#include "AThread.h"

class Ponger;
class message_from_pong;

// Type of message sent from Ping
class message_from_ping {
public: std::string str;
};

//Test class
class Pinger : public AThread {
public:
	I_AM_A_THREAD;
	Pinger();
	void process(const message_from_pong& message);
	Ponger* recipient;
};

#endif
