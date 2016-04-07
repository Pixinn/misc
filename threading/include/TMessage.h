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