#include "AThread.h"

using namespace std;

AThread::AThread(void)
{	}

AThread::~AThread(void) noexcept
{	}



void AThread::run(void)
{
	if (_isRunning) {
		throw std::runtime_error("Thread already running");
	}
	_isRunning = true;
	_hasToStop = false;
	try {
		auto mailbox = std::thread([this] {
			while (!_hasToStop) {
				auto message = _messages.pop_front();
				message->execute();
			}
			_isRunning = false;
		});
		_mailbox = std::move(mailbox);
	}
	catch(std::exception) {
		_isRunning = false;
		throw;
	}
}



void AThread::stop(void) noexcept
{
	STOP msgStop;
	_messages.emplace_front(new TMessage<STOP>(std::forward<STOP>(msgStop), [this](const STOP& msg) {
		process(msg);
	}));
}


void AThread::join(void) noexcept
{
	_mailbox.join();
}


void AThread::process(STOP) noexcept
{
	_hasToStop = true;
	_messages.clear();
}