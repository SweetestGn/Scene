#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lspointtypes.h>
#include <core_api/lsiterator.h>
#include <core_api/lsresult.h>

namespace SCENE_API {

// Forward declarations
class LSPointSelection_Implementation;

/// Interface class to access information and functionality of spatial 
/// point selections.
/// \version SCENE API Version 2.0.0.
class LSPointSelection : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSPointSelection)

public:

	/// Gets an iterator to run over all points which are part of the
	/// point selection.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSIterator<LSPointXYZRGB> getPointSelectionIterator();

protected:
	LS_INTERFACE(LSPointSelection, LSInterface)
};

}
