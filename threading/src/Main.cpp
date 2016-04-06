#include <iostream>
#include <string>

#include "AThread.h"

using namespace std;


class Receiver : public AThread
{
public:
	I_AM_A_THREAD

	void process(const std::string& str ) {
		cout << str << endl;
	}
};


int main(int, char**)
{
	try {
		Receiver receiver;
		receiver.run();
		receiver.send(string("Hello World 1"));
		receiver.send(string("Hello World 2"));
		receiver.send(string("Hello World 3"));
		receiver.stop(); //this stop command shall be executed *before* Hellow World 2 & 3 !
		receiver.join();
		receiver.send(string("Tintin"));
		receiver.run();
		receiver.stop();
		receiver.join();
	}
	catch (std::exception& e ) {
		cout << "ERROR: " << e.what();
	}
	return 0;
}
