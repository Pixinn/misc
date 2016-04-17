#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include "Logger.h"
#include "Pinger.h"
#include "Ponger.h"

using namespace std;


//Main test
int main(int, char**)
{
	try {
		Logger& logger = Logger::GetInstance();
		logger.run();
        logger.send(string("Logger STARTED!"), SYNC);
		Pinger pinger;
		Ponger ponger;
		pinger.recipient = &ponger;
		ponger.recipient = &pinger;
		pinger.run();
        logger.send(string("Pinger STARTED!"), SYNC);
		ponger.run();
        logger.send(string("Ponger STARTED!"), SYNC);

		//bootstrap: starts the threads!
		message_from_pong msg;
		msg.number = 0;
        pinger.send(std::move(msg), SYNC);

        std::this_thread::sleep_for( std::chrono::seconds(3) );
		pinger.stop();
		ponger.stop();

		//logger is slower: it needs more time to process its messages
        std::this_thread::sleep_for( std::chrono::seconds(15) );
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

