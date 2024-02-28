#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsreftype.h>

namespace SCENE_API {

///The base class for all API events.
/// \version SCENE API Version 2.0.0.
class LSEvent : public LSRefType
{
	LS_UNCOPYABLE(LSEvent)

public:

	/// Constructor. 
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSEvent();

	/// Destructor.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT virtual ~LSEvent();

	/// Query whether this event has been consumed. 
	/// \return	true if the event has been consumed, false otherwise. 
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool isConsumed() const;

	/// Consumes this event if the event can be consumed. This will
	/// prevent the event from being processed in the default manner.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void consume();

protected:
	// Whether the event may be consumed
	bool m_consumable;

	// Whether the event has been consumed.
	bool m_consumed;
};

}
