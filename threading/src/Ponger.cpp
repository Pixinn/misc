#include "Pinger.h"
#include "Logger.h"
#include "Ponger.h"

Ponger::Ponger()
{	}

void Ponger::process(const message_from_ping& message) {
	Logger::GetInstance().send( std::move(message.str) );
	message_from_pong my_msg;
	my_msg.number = ++_count;
	recipient->send(std::move(my_msg));
}