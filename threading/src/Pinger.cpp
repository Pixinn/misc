
#include <string>

#include "Ponger.h"
#include "Logger.h"
#include "Pinger.h"

using namespace std;

Pinger::Pinger()
{	}

void Pinger::process(const message_from_pong& message )
{
	Logger::GetInstance().send( string("PONG ") + to_string(message.number));
	message_from_ping my_msg;
	my_msg.str = "PING";
	recipient->send(std::move(my_msg));
}