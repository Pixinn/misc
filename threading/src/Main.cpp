#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include "Logger.h"
#include "Pinger.h"
#include "Ponger.h"

using namespace std;
using namespace std::chrono_literals;


//Main test
int main(int, char**)
{
	try {
		Logger& logger = Logger::GetInstance();
		logger.run();
		logger.send(string("Logger STARTED!"));
		Pinger pinger;
		Ponger ponger;
		pinger.recipient = &ponger;
		ponger.recipient = &pinger;
		pinger.run();
		logger.send(string("Pinger STARTED!"));
		ponger.run();
		logger.send(string("Ponger STARTED!"));

		//bootstrap: starts the threads!
		message_from_pong msg;
		msg.number = 0;
		pinger.send(std::move(msg));

		std::this_thread::sleep_for(20s);

		pinger.stop();
		ponger.stop();
		logger.stop();
		pinger.join();
		ponger.join();
		logger.join();
	}
	catch (std::exception& e ) {
		cout << "ERROR: " << e.what();
	}
	return 0;
}

