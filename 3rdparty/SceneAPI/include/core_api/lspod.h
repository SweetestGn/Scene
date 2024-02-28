#pragma once

#include <core_api/lsglobaldefinitions.h>

#include <vector>
#include <list>
#include <set>
#include <map>

namespace SCENE_API {

/// Helper class to manage the conversion of different data structures to POD
/// (Plain Old Data) format so that they can safely be passed over the dll 
/// boundary.
/// \version	SCENE API Version 2.0.0.
template<class T>
class LSPod
{
public:
	/// Creates an LSPod instance from an existing value type.
	/// \version	SCENE API Version 2.0.0.
	LSPod(const T& from);

	// Construction and assignment from existing LSPod instances.
	/// \version	SCENE API Version 2.0.0.
	LSPod(const LSPod<T>& from);
	LSPod<T>& operator=(const LSPod<T>& from);

	/// Destroys the LSPod instance.
	/// \version	SCENE API Version 2.0.0.
	virtual ~LSPod();

	/// Gets the contained value.
	/// \version	SCENE API Version 2.0.0.
	T get();

	// https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	T data;
};

//-----------------------------------------------------------------------------
template <class T>
LSPod<T>::LSPod(const T& from)
	: data(from)
{}

//-----------------------------------------------------------------------------
template <class T>
LSPod<T>::LSPod(const LSPod<T>& from)
	: data(from.data)
{}

//-----------------------------------------------------------------------------
template <class T>
LSPod<T>& LSPod<T>::operator=(const LSPod<T>& from)
{
	data = from.data;
	return *this;
}

//-----------------------------------------------------------------------------
template <class T>
LSPod<T>::~LSPod()
{}

//-----------------------------------------------------------------------------
template <class T>
T LSPod<T>::get()
{
	return data;
}

//-----------------------------------------------------------------------------
// L S P o d D a t a A r r a y
//-----------------------------------------------------------------------------
template <class T>
class LSPodDataArray
{
public:
	LSPodDataArray(size_t size)
	{
		if (size > 0)
			dataArray = new T[size];
		else
			dataArray = 0;
	}

	virtual ~LSPodDataArray()
	{
		if (dataArray)
			delete[] dataArray;
	}

	T* dataArray;
};

//-----------------------------------------------------------------------------
// L S P o d < s t d : : v e c t o r >
//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
class LSPod<std::vector<_Ty, _Alloc> >
{
public:
	/// \brief	Creates an LSPod instance from an existing vector.
	LSPod(const std::vector<_Ty, _Alloc>& from);

	// \brief	Construction and assignment from existing LSPod instances.
	LSPod(const LSPod<std::vector<_Ty, _Alloc> >& from);
	LSPod<std::vector<_Ty, _Alloc> >& operator=(const LSPod<std::vector<_Ty, _Alloc> >& from);

	/// \brief	Destroys the LSPod instance.
	virtual ~LSPod();

	/// \brief	Gets the contained vector.
	std::vector<_Ty, _Alloc> get() const;

private:
	size_t size;
	LSPodDataArray<LSPod<_Ty>*>* data;
};

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::vector<_Ty, _Alloc> >::LSPod(const std::vector<_Ty, _Alloc>& from)
	: size(from.size())
	, data(new LSPodDataArray<LSPod<_Ty>*>(from.size()))
{
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Ty>(from[i]);
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::vector<_Ty, _Alloc> >::LSPod(const LSPod<std::vector<_Ty, _Alloc> >& from)
	: size(from.size)
	, data(new LSPodDataArray<LSPod<_Ty>*>(from.size))
{
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Ty>(*(from.data->dataArray[i]));
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::vector<_Ty, _Alloc> >& LSPod<std::vector<_Ty, _Alloc> >::operator=(const LSPod<std::vector<_Ty, _Alloc> >& from)
{
	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];
	delete data;

	size = from.size;
	data = new LSPodDataArray<LSPod<_Ty>*>(from.size);
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Ty>(*(from.data->dataArray[i]));

	return *this;
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::vector<_Ty, _Alloc> >::~LSPod()
{
	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];
	delete data;
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
std::vector<_Ty, _Alloc> LSPod<std::vector<_Ty, _Alloc> >::get() const
{
	std::vector<_Ty, _Alloc> v;
	v.reserve(size);
	for (size_t i = 0; i < size; ++i)
		v.push_back(data->dataArray[i]->get());
	return v;
}

//-----------------------------------------------------------------------------
// L S P o d < s t d : : l i s t >
//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
class LSPod<std::list<_Ty, _Alloc> >
{
public:
	/// \brief	Creates an LSPod instance from an existing list.
	LSPod(const std::list<_Ty, _Alloc>& from);

	// \brief	Construction and assignment from existing LSPod instances.
	LSPod(const LSPod<std::list<_Ty, _Alloc> >& from);
	LSPod<std::list<_Ty, _Alloc> >& operator=(const LSPod<std::list<_Ty, _Alloc> >& from);

	/// \brief	Destroys the LSPod instance.
	virtual ~LSPod();

	/// \brief	Gets the contained list.
	std::list<_Ty, _Alloc> get() const;

private:
	size_t size;
	LSPodDataArray<LSPod<_Ty>*>* data;
};

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::list<_Ty, _Alloc> >::LSPod(const std::list<_Ty, _Alloc>& from)
	: size(from.size())
	, data(new LSPodDataArray<LSPod<_Ty>*>(from.size()))
{
	size_t i = 0;
	typename std::list<_Ty, _Alloc>::const_iterator iter = from.begin();
	for (; iter != from.end(); ++iter, ++i)
		data->dataArray[i] = new LSPod<_Ty>(*iter);
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::list<_Ty, _Alloc> >::LSPod(const LSPod<std::list<_Ty, _Alloc> >& from)
	: size(from.size)
	, data(new LSPodDataArray<LSPod<_Ty>*>(from.size))
{
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Ty>(*(from.data->dataArray[i]));
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::list<_Ty, _Alloc> >& LSPod<std::list<_Ty, _Alloc> >::operator=(const LSPod<std::list<_Ty, _Alloc> >& from)
{

	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];
	delete data;

	size = from.size;
	data = new LSPodDataArray<LSPod<_Ty>*>(from.size);
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Ty>(*(from.data->dataArray[i]));

	return *this;
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
LSPod<std::list<_Ty, _Alloc> >::~LSPod()
{
	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];

	delete data;
}

//-----------------------------------------------------------------------------
template<class _Ty, class _Alloc>
std::list<_Ty, _Alloc> LSPod<std::list<_Ty, _Alloc> >::get() const
{
	std::list<_Ty, _Alloc> l;
	for (size_t i = 0; i < size; ++i)
		l.push_back(data->dataArray[i]->get());
	return l;
}

//-----------------------------------------------------------------------------
// L S P o d < s t d : : s e t >
//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
class LSPod<std::set<_Kty, _Pr, _Alloc> >
{
public:
	/// \brief	Creates an LSPod instance from an existing set.
	LSPod(const std::set<_Kty, _Pr, _Alloc>& from);

	// \brief	Construction and assignment from existing LSPod instances.
	LSPod(const LSPod<std::set<_Kty, _Pr, _Alloc> >& from);
	LSPod<std::set<_Kty, _Pr, _Alloc> >& operator=(const LSPod<std::set<_Kty, _Pr, _Alloc> >& from);

	/// \brief	Destroys the LSPod instance.
	virtual ~LSPod();

	/// \brief	Gets the contained set.
	std::set<_Kty, _Pr, _Alloc> get() const;

private:
	size_t size;
	LSPodDataArray<LSPod<_Kty>*>* data;
};

//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
LSPod<std::set<_Kty, _Pr, _Alloc> >::LSPod(const std::set<_Kty, _Pr, _Alloc>& from)
	: size(from.size())
	, data(new LSPodDataArray<LSPod<_Kty>*>(from.size()))
{
	size_t i = 0;
	typename std::set<_Kty, _Pr, _Alloc>::const_iterator iter = from.begin();
	for (; iter != from.end(); ++iter, ++i)
		data->dataArray[i] = new LSPod<_Kty>(*iter);
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
LSPod<std::set<_Kty, _Pr, _Alloc> >::LSPod(const LSPod<std::set<_Kty, _Pr, _Alloc> >& from)
	: size(from.size)
	, data(new LSPodDataArray<LSPod<_Kty>*>(from.size))
{
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Kty>(*(from.data->dataArray[i]));
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
LSPod<std::set<_Kty, _Pr, _Alloc> >& LSPod<std::set<_Kty, _Pr, _Alloc> >::operator=(const LSPod<std::set<_Kty, _Pr, _Alloc> >& from)
{
	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];
	delete data;

	data = new LSPodDataArray<LSPod<_Kty>*>(from.size);
	size = from.size;
	for (size_t i = 0; i < size; ++i)
		data->dataArray[i] = new LSPod<_Kty>(*(from.data->dataArray[i]));

	return *this;
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
LSPod<std::set<_Kty, _Pr, _Alloc> >::~LSPod()
{
	for (size_t i = 0; i < size; ++i)
		delete data->dataArray[i];

	delete data;
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Pr, class _Alloc>
std::set<_Kty, _Pr, _Alloc> LSPod<std::set<_Kty, _Pr, _Alloc> >::get() const
{
	std::set<_Kty, _Pr, _Alloc> s;
	for (size_t i = 0; i < size; ++i)
		s.insert(data->dataArray[i]->get());
	return s;
}

//-----------------------------------------------------------------------------
// L S P o d < s t d : : m a p >
//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
class LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >
{
public:
	/// \brief	Creates an LSPod instance from an existing map.
	LSPod(const std::map<_Kty, _Ty, _Pr, _Alloc>& from);

	// \brief	Construction and assignment from existing LSPod instances.
	LSPod(const LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& from);
	LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& operator=(const LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& from);

	/// \brief	Destroys the LSPod instance.
	virtual ~LSPod();

	/// \brief	Gets the contained map.
	std::map<_Kty, _Ty, _Pr, _Alloc> get() const;

private:
	size_t size;
	LSPodDataArray<LSPod<_Kty>*>* keys;
	LSPodDataArray<LSPod<_Ty>*>* values;
};

//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >::LSPod(const std::map<_Kty, _Ty, _Pr, _Alloc>& from)
	: size(from.size())
	, keys(new LSPodDataArray<LSPod<_Kty>*>(from.size()))
	, values(new LSPodDataArray<LSPod<_Ty>*>(from.size()))
{
	size_t i = 0;
	typename std::map<_Kty, _Ty, _Pr, _Alloc>::const_iterator iter = from.begin();
	for (; iter != from.end(); ++iter, ++i)
	{
		keys->dataArray[i] = new LSPod<_Kty>(iter->first);
		values->dataArray[i] = new LSPod<_Ty>(iter->second);
	}
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >::LSPod(const LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& from)
	: size(from.size)
	, keys(new LSPodDataArray<LSPod<_Kty>*>(from.size))
	, values(new LSPodDataArray<LSPod<_Ty>*>(from.size))
{
	for (size_t i = 0; i < size; ++i)
	{
		keys->dataArray[i] = new LSPod<_Kty>(*(from.keys->dataArray[i]));
		values->dataArray[i] = new LSPod<_Ty>(*(from.values->dataArray[i]));
	}
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >::operator=(const LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >& from)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete keys->dataArray[i];
		delete values->dataArray[i];
	}
	delete keys;
	keys = nullptr;
	delete values;
	values = nullptr;

	keys = new LSPodDataArray<LSPod<_Kty>*>(from.size);
	values = new LSPodDataArray<LSPod<_Ty>*>(from.size);
	size = from.size;
	for (size_t i = 0; i < size; ++i)
	{
		keys->dataArray[i] = new LSPod<_Kty>(*(from.keys->dataArray[i]));
		values->dataArray[i] = new LSPod<_Ty>(*(from.values->dataArray[i]));
	}

	return *this;
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >::~LSPod()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete keys->dataArray[i];
		delete values->dataArray[i];
	}

	delete keys;
	delete values;
}

//-----------------------------------------------------------------------------
template<class _Kty, class _Ty, class _Pr, class _Alloc>
std::map<_Kty, _Ty, _Pr, _Alloc> LSPod<std::map<_Kty, _Ty, _Pr, _Alloc> >::get() const
{
	std::map<_Kty, _Ty, _Pr, _Alloc> m;
	for (size_t i = 0; i < size; ++i)
		m[keys->dataArray[i]->get()] = values->dataArray[i]->get();
	return m;
}

}
