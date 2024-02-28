#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lstrackable.h>
#include <core_api/lsslot.h>

namespace SCENE_API {

// Forward declarations
class LSSignalBase_Implementation;
template <typename T> class LSSignal_Implementation;

/// Base class for all signals.
/// \version SCENE API Version 2.0.0.
class LSSignalBase : public LSInterface
{
protected:
	LS_INTERFACE(LSSignalBase, LSInterface);
};

/// General signal interface which provides functionality to connect
/// arbitrary function handlers to a specific signal. The function
/// handler has to match the function signature of the signal and can
/// either be a free function or a member function of a LSTrackable
/// derived class.
/// \version SCENE API Version 2.0.0.
template<class Event>
class LSSignal : public LSSignalBase
{
public:
	LSSignal();
	LSSignal(const LSSignal& signal);
	LSSignal& operator=(const LSSignal&);
	virtual ~LSSignal();

	/// Adds a free function as a function handler for this signal. The
	/// function needs to have a matching signature with a void return 
	/// value and an event of the specified type as a single argument.
	/// \param	handler	A function pointer to the free function which should
	/// be added as a function handler.
	/// \version	SCENE API Version 2.0.0.
	void connect( void(*handler)(Event))
	{
		connect(new LSSlot<Event>(handler));
	}

	/// Adds a member function as a function handler for this signal. 
	/// The function needs to be a member of an LSTrackable derived
	/// class and needs to have a matching signature with a void return 
	/// value and an event of the specified type as a single argument.
	/// \param	trackable	The trackable instance whose member function should
	/// be called when the signal is triggered.
	/// \param	handler	A function pointer to the free function which should
	/// be added as a function handler.
	/// \version	SCENE API Version 2.0.0.
	template<class Trackable>
	void connect(Trackable* trackable, void(Trackable::*handler)(Event))
	{
		connect(new LSSlot<Event, Trackable>(trackable, handler));
	}

	/// Triggers the signals and calls the connected function handlers.
	/// \param	event	The event which is passed to the connected function
	/// handlers.
	/// \param	synchronize	Whether the call should wait until all function
	/// handler have been called.
	/// \version	SCENE API Version 2.0.0.
	void operator()(Event event, bool synchronize = false);

protected:
	void connect(ref_ptr<LSSlotBase<Event> > slot);

private:
	LS_INTERFACE_TEMPLATE(LSSignal, Event, LSSignalBase);
};

}
