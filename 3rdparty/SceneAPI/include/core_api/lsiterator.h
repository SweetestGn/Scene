#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>

namespace SCENE_API {

// Forward declarations
template<typename ValueT> class LSIterator_Implementation;

/// A general iterator interface for arbitrary collections. 
/// \version SCENE API Version 2.0.0.
template<typename ValueT>
class LSIterator : public LSInterface
{
public:

	/// Constructs a null iterator.
	/// \version	SCENE API Version 2.0.0.
	LSIterator();

	/// Constructs a copy of the iterator \a iter.
	/// \param	iter	The iterator from which to create a copy.
	/// \version	SCENE API Version 2.0.0.
	LSIterator(const LSIterator<ValueT>& iter);

	/// Assigns a copy of the iterator \a iter to this iterator.
	/// \param	iter	The iterator which is assigned to this iterator.
	/// \version	SCENE API Version 2.0.0.
	LSIterator& operator=(const LSIterator<ValueT>& iter);


	/// Advances the iterator to the next element of the container. 
	/// \return	true if the iterator could be set to the next element, false
	///			if the iterator passed the end of the container.
	/// \version	SCENE API Version 2.0.0.
	bool moveNext();

	/// Gets the element at which the iterator currently points. 
	/// \return	The element at which the iterator currently points.
	/// \version	SCENE API Version 2.0.0.
	ValueT getCurrent() const;

	/// Gets the element at which the iterator currently points.
	/// \param[out]	out	The element at which the iterator currently points.
	/// \version	SCENE API Version 2.0.0.
	void getCurrent(ValueT& out) const;

	/// Filters the elements returned by the iterator based on a given
	/// filter function. The input function \a func has to be a function type 
	/// which takes a const reference to the value type and returns an boolean 
	/// based on the filter result.
	/// \return	The filtered iterator.
	/// \version	SCENE API Version 2.0.0.
	LSIterator<ValueT> where(bool (*func)(const ValueT&)) const;


	/// Default allocation function. Overloaded in order to always
	/// allocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	void* operator new(size_t tSize);
	/// Default deallocation function. Overloaded in order to always
	/// deallocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	void  operator delete(void* p);

protected:
	LS_INTERFACE_TEMPLATE(LSIterator, ValueT, LSInterface)
};

}
