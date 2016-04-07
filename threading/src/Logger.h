#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

#include "AThread.h"

//Logger class
class Logger : public AThread {
public:
	I_AM_A_THREAD;
	void process(const std::string& log);

	static Logger& GetInstance(void) {
		return Instance;
	}
private:
	Logger() = default;
	static Logger Instance;
};


#endif
