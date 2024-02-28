#pragma once

#include <core_api/lsglobaldefinitions.h>

namespace SCENE_API {

/// Result class containing different result codes for API methods.
/// \version	SCENE API Version 2.0.0.
struct LSResult
{
	/// The different result codes for the API methods.
	enum Result
	{
		Ok, ///< Operation succeeded without errors.
		Internal, ///< An internal error occurred.
		Unauthorized, ///< You are not authorized for this operation without an corresponding API key.
		InvalidRequest, ///< Request not allowed in this state or you supplied invalid parameters.
		DuplicateName, ///< The item exists already.
		IncompatibleVersion, ///< Software version does not match, for example while loading projects.
		ReadWrite, ///< General read/write IO error.
		Network, ///< General network IO error.
		Compatibility ///< Project contains object from a newer SCENE version. Can be open in 'Read-Only'.
	};
};

}
