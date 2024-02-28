#pragma once

#include <core_api/lsglobaldefinitions.h>

namespace SCENE_API {

/// Provides a lifetime managing pointer for all LSRefType derived
/// classes. Instances managed by ref_ptrs are kept alive as long as a
/// ref_ptr exists to the object instance and are automatically 
/// destroyed once the last ref_pointer pointing to the instance is
/// destroyed.
/// \version SCENE API Version 2.0.0.
template<class T>
class ref_ptr
{
public:

	ref_ptr() throw() : m_obj(0)
	{
	}

	ref_ptr(T* obj) : m_obj(obj)
	{
		if (m_obj != 0)
			m_obj->ref();
	}

	ref_ptr(const ref_ptr& rhs) : m_obj(rhs.get())
	{
		if (m_obj != 0)
			m_obj->ref();
	}

	template<class U>
	ref_ptr(ref_ptr<U> const & rhs ) : m_obj( rhs.get())
	{
		if (m_obj != 0)
			m_obj->ref();
	}

	~ref_ptr()
	{
		if (m_obj != 0)
			m_obj->unref();
	}

	ref_ptr& operator=(ref_ptr const & rhs)
	{
		if (m_obj)
			m_obj->unref();

		m_obj = rhs.get();

		if (m_obj)
			m_obj->ref();

		return *this;
	}

	ref_ptr& operator=(T* rhs)
	{
		if (m_obj)
			m_obj->unref();

		m_obj = rhs;

		if (m_obj)
			m_obj->ref();

		return *this;
	}

	template<class U> 
	ref_ptr & operator=(ref_ptr<U> const & rhs)
	{
		if (m_obj)
			m_obj->unref();

		m_obj = rhs.get();

		if (m_obj)
			m_obj->ref();

		return *this;
	}

	void reset() throw()
	{
		if (m_obj)
			m_obj->unref();

		m_obj = 0;
	}

	void reset(T* rhs)
	{
		if (m_obj)
			m_obj->unref();

		m_obj = rhs;

		if (m_obj)
			m_obj->ref();
	}

	T* get() const throw()
	{
		return m_obj;
	}

	T& operator*() const
	{
		return *m_obj;
	}

	T* operator->() const
	{
		return m_obj;
	}

	// Safe bool idiom for bool comparison
	typedef T* ref_ptr<T>::*unspecified_bool_type;
	operator unspecified_bool_type() const
	{
		return m_obj == 0 ? 0: &ref_ptr<T>::m_obj;
	}

	/// Swap the pointers
	void swap(ref_ptr<T>& other)
	{
		std::swap(m_obj, other.m_obj);
	}

private:
	T* m_obj;
};

template<class T, class U> 
inline bool operator==(ref_ptr<T> const & p1, ref_ptr<U> const & p2)
{
	return p1.get() == p2.get();
}

template<class T, class U> 
inline bool operator!=(ref_ptr<T> const & p1, ref_ptr<U> const & p2)
{
	return p1.get() != p2.get();
}

template<class T, class U> 
inline bool operator==(ref_ptr<T> const & p1, U* p2)
{
	return p1.get() == p2;
}

template<class T, class U> 
inline bool operator!=(ref_ptr<T> const & p1, U* p2)
{
	return p1.get() != p2;
}

template<class T, class U> 
inline bool operator==(T* p1, ref_ptr<U> const & p2)
{
	return p1 == p2.get();
}

template<class T, class U> 
inline bool operator!=(T* p1, ref_ptr<U> const & p2)
{
	return p1 != p2.get();
}

template<class T> 
inline bool operator<(ref_ptr<T> const & p1, ref_ptr<T> const & p2)
{
	return std::less<T *>()(p1.get(), p2.get());
}

template<class T> void swap(ref_ptr<T> & lhs, ref_ptr<T> & rhs)
{
	lhs.swap(rhs);
}

template<class T, class U> 
ref_ptr<T> static_pointer_cast(ref_ptr<U> const & p)
{
	return static_cast<T *>(p.get());
}

template<class T, class U> 
ref_ptr<T> const_pointer_cast(ref_ptr<U> const & p)
{
	return const_cast<T *>(p.get());
}

template<class T, class U> 
ref_ptr<T> dynamic_pointer_cast(ref_ptr<U> const & p)
{
	return dynamic_cast<T *>(p.get());
}

}
