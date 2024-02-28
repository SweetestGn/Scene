#pragma once

#include <core_api/lsreftype.h>
#include <core_api/lsinterface.h>
#include <core_api/lsstring.h>

namespace SCENE_API {

// Forward declarations
class LSError_Implementation;

/// An error is caused when the API unexpectedly fails to function properly.
/// \version	SCENE API Version 2.0.14.
class LSError : public LSInterface, public LSRefType
{
public:
	/// Constructs a copy of an error.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSError(const LSError& from);
	CORE_API_EXPORT LSError& operator=(const LSError& from);

	/// The name identifies the error type.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSString getName() const;

	/// The message describes the error cause.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSString getMessage() const;

	/// Allocation / Deallocation of error instances
	CORE_API_EXPORT void* operator new(size_t tSize);
	CORE_API_EXPORT void  operator delete(void* p);

protected:
	LS_INTERFACE(LSError, LSInterface)
};

}