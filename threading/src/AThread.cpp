/*
*  Copyright (C) Christophe Meneboeuf <christophe@xtof.info>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
	_hasToStop = true;
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
	_messages.clear();
}