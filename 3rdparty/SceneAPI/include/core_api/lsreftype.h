#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>

namespace SCENE_API {

/// Base class for all API class which support automatic memory 
/// management through reference counting.
/// \version SCENE API Version 2.0.0.
class LSRefType 
{
	// ref_ptrs may be used for the automatic memory management of LSRefType
	// derived classes. ref_ptrs are therefore allowed to access the internal
	// reference counting methods.
	template<class T> friend class ref_ptr;

protected:
	CORE_API_EXPORT LSRefType();
	CORE_API_EXPORT virtual ~LSRefType();

	/// Increments the internal reference counter.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void ref() const;

	/// Decrements the internal reference counter. Destroys the 
	/// instance if the reference count reaches zero.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void unref() const;

private:
	mutable long m_refCount;
};

}
