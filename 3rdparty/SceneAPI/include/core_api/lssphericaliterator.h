#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsiterator.h>

namespace SCENE_API
{

// Forward declarations
template<typename ValueT>
class LSSphericalIterator_Implementation;

/// A specialized iterator which may be run on organized scans and
/// additionally provides access to the row and column of the current
/// scan point.
/// \version	SCENE API Version 2.0.31.
template<typename ValueT>
class LSSphericalIterator : public LSIterator<ValueT>
{
public:
	/// Constructs a null iterator.
	/// \version	SCENE API Version 2.0.31.
	LSSphericalIterator();

	/// Constructs a copy of the iterator \a iter.
	/// \param	iter	The iterator from which to create a copy.
	/// \version	SCENE API Version 2.0.31.
	LSSphericalIterator(const LSSphericalIterator<ValueT>& iter);

	/// Assigns a copy of the iterator \a iter to this iterator.
	/// \param	iter	The iterator which is assigned to this iterator.
	/// \version	SCENE API Version 2.0.31.
	LSSphericalIterator& operator=(const LSSphericalIterator<ValueT>& iter);

	/// Gets the column of the scan point at which the iterator
	/// currently points.
	/// \version	SCENE API Version 2.0.31.
	int getCurrentCol() const;

	/// Gets the row of the scan point at which the iterator
	/// currently points.
	/// \version	SCENE API Version 2.0.31.
	int getCurrentRow() const;

	/// Default allocation function. Overloaded in order to always
	/// allocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.31.
	void* operator new(size_t tSize);
	/// Default deallocation function. Overloaded in order to always
	/// deallocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.31.
	void operator delete(void* p);

protected:
	LS_INTERFACE_TEMPLATE2(LSSphericalIterator, ValueT, LSIterator)
};

}
