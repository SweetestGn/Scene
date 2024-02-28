#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>

namespace SCENE_API {

// Forward declarations
class LSTrackable_Implementation; 

/// Base class for all classes which connect member functions to 
/// LSSignal instances.
/// \version SCENE API Version 2.0.0.
class LSTrackable : public LSInterface
{
public:
	CORE_API_EXPORT LSTrackable();
	CORE_API_EXPORT LSTrackable(const LSTrackable&);
	CORE_API_EXPORT LSTrackable& operator=(const LSTrackable&);
	CORE_API_EXPORT virtual ~LSTrackable();

private:
	LS_INTERFACE(LSTrackable, LSInterface)
};

}
