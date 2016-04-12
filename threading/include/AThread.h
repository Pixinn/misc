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



#ifndef ATHREAD_H_
#define ATHREAD_H_

#include <memory>
#include <atomic>
#include <functional>
#include <exception>

#include "TMessage.h"
#include "TDequeConcurrent.h"


//CLASS
//! \brief Base class for a thread
//!  
//!		   This class is based on a background worker thread waiting messages to process.
//!		   The message processors must be provided by the concrete daughter classes.
//!        These daughter classes have to put the I_AM_A_THREAD macro in their public section
class AThread
{
	//TODO make the thread restartable. Need to clear _messages?
	//TODO Implement a *clean* defered delete

public:
	//! \brief Starts the thread and waits for messages to process
	void run(void);
	//! \brief Ask the thread to stop after its current work
	void stop(void) noexcept;
	//! \brief Joins the thread
	void join(void) noexcept;

protected:
	AThread(void);
	AThread(AThread&&) = default;
	virtual ~AThread(void) noexcept;
	AThread& operator=(AThread&&) = default;


	TDequeConcurrent<std::unique_ptr<IMessage>> _messages;  //!< Incoming messages

private:
	struct STOP {};		//!< Dedicated private structure used to ask the thread to stop
	//! \brief Processing the STOP message sent by stop()
	void process(STOP) noexcept;

	std::thread _mailbox;					//!< Handle on the running thread waiting for messages
	std::atomic<bool> _isRunning = false;	//!< Is the thread running?
	std::atomic<bool> _hasToStop = false;	//!< Asks the thread to stop
};


//MACRO
#define I_AM_A_THREAD 	\
template<typename TDATA> \
void send(TDATA&& data) { \
	_messages.emplace_back(new TMessage<TDATA>(std::forward<TDATA>(data), [this](const TDATA& msg) { \
		process(msg); \
	})); \
}
 
#endif // !ATHREAD_H_