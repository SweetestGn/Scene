#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lsresult.h>

namespace SCENE_API {

// Forward declarations
class LSFutureTask_Implementation;

/// A task object representing an asynchronous operation.
/// \version	SCENE API Version 2.0.0.
class LSFutureTask : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSFutureTask)

public:

	/// Aborts the associated operation.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT void abort();

	/// Returns whether the associated operation has been finished.
	/// \return	true if the operation has been finished, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool isFinished() const;

	/// Returns the progress state of the associated operation.
	/// \return	The progress state of the associated operation in percent.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT int getProgress() const;

	/// Gets the result code of the associated operation. Blocks until the result is available.
	/// \return	The result code of the associated operation.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSResult::Result getResult() const;
	
protected:
	LS_INTERFACE(LSFutureTask, LSInterface);
	friend class LSScanner_Implementation;
};

}
