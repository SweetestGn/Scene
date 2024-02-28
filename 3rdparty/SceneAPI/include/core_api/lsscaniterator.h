#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsiterator.h>

namespace SCENE_API {

// Forward declarations
template<typename ValueT> class LSScanIterator_Implementation;

/// A specialized iterator which may be run on organized scans and 
/// additionally provides access to the row and column of the current
/// scan point.
/// \version	SCENE API Version 2.0.0.
template<typename ValueT>
class LSScanIterator : public LSIterator<ValueT>
{
public:

	/// Constructs a null iterator.
	/// \version	SCENE API Version 2.0.0.
	LSScanIterator();

	/// Constructs a copy of the iterator \a iter.
	/// \param	iter	The iterator from which to create a copy.
	/// \version	SCENE API Version 2.0.0.
	LSScanIterator(const LSScanIterator<ValueT>& iter);

	/// Assigns a copy of the iterator \a iter to this iterator.
	/// \param	iter	The iterator which is assigned to this iterator.
	/// \version	SCENE API Version 2.0.0.
	LSScanIterator& operator=(const LSScanIterator<ValueT>& iter);


	/// Gets the column of the scan point at which the iterator
	/// currently points.
	/// \version	SCENE API Version 2.0.0.
	int getCurrentCol() const;

	/// Gets the row of the scan point at which the iterator
	/// currently points.
	/// \version	SCENE API Version 2.0.0.
	int getCurrentRow() const;


	/// Default allocation function. Overloaded in order to always
	/// allocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	void* operator new(size_t tSize);
	/// Default deallocation function. Overloaded in order to always
	/// deallocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	void  operator delete(void* p);

protected:
	LS_INTERFACE_TEMPLATE2(LSScanIterator, ValueT, LSIterator)
};

}
