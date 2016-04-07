#include <iostream>
#include <string>

#include "Logger.h"

using namespace std;


Logger Logger::Instance;

void Logger::process(const std::string& log) {
	cout << log << endl;
}
