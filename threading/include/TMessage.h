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


#ifndef ITMESSAGE_H_
#define ITMESSAGE_H_

#include <memory>
#include <functional>
#include <utility>



//! \brief Interface for Messages
class IMessage
{
public:
	virtual void execute(void) = 0;
};


//! \brief  Templated interface to a message carrying TDATA
//!  
//!			The carried data are unmutable
//!         The is built from the data to be carried and the process to perform over these data
//!			
template< typename TDATA >
class TMessage : public IMessage
{
public:
	TMessage(TDATA& data, std::function<void(const TDATA&)> processor) :
		_data( data ), _processor(processor)
	{	}
	TMessage( TDATA&& data, std::function<void(const TDATA&)> processor ) :
		_data( std::move(data) ), _processor( processor )
	{	}
	
	// ++ Force generation of default move operations
	TMessage(TMessage&&) = default;
	TMessage& operator=(TMessage&&) = default;

	// ++ Forbid default copy operations
	TMessage(const TMessage&) = delete;
	TMessage& operator = (const TMessage&) = delete;

	// ++ Interface to be implemented
	//! \brief Executes the message processor
	void execute(void) override	{
		_processor(_data);
	}
private:
	 const TDATA _data;								//!< Data carried by the message
	 std::function<void(const TDATA&)>  _processor; //!< Function processing the data
};


#endif // !ITMESSAGE_H_