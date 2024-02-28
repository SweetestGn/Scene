#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsreftype.h>
#include <core_api/lsstring.h>

namespace SCENE_API {

/// The LSTask class which represents a generic function object.
/// \version	SCENE API Version 2.0.0.
class LSTask : public LSRefType
{
	/// @name Task interface
	//@{

public:
	/// Overwritable method which specifies the functionality to be
	/// executed when the task is performed.
	/// \version	SCENE API Version 2.0.0.
	virtual void perform() = 0;

	//@}
};

}
