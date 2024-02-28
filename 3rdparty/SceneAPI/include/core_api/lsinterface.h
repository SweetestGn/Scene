#pragma once

#include <core_api/lsglobaldefinitions.h>

namespace SCENE_API {

// Forward declarations
class LSInterface_Implementation;

/// The LSInterface class acts as a base class for all classes which
/// act as an interface to an internal implementation.
/// \version SCENE API Version 2.0.0.
class LSInterface 
{
	LS_UNCOPYABLE(LSInterface)

protected:
	CORE_API_EXPORT explicit LSInterface(LSInterface_Implementation*);
public:
	CORE_API_EXPORT virtual ~LSInterface();

private:
	friend class LSInterface_Implementation;
	LSInterface_Implementation* m_implementation;
};

#define LS_INTERFACE(Class, BaseClass) \
	friend class Class##_Implementation; \
	inline Class(Class##_Implementation* implementation) : BaseClass((BaseClass##_Implementation*)implementation) {}

#define LS_INTERFACE_TEMPLATE(Class, TemplateType, BaseClass) \
	template <class T> friend class Class##_Implementation; \
	inline Class(Class##_Implementation<TemplateType>* implementation) : BaseClass((BaseClass##_Implementation*)implementation) {}

#define LS_INTERFACE_TEMPLATE2(Class, TemplateType, BaseClass) \
	template <class T> friend class Class##_Implementation; \
	inline Class(Class##_Implementation<TemplateType>* implementation) : BaseClass<TemplateType>((BaseClass##_Implementation<TemplateType>*)implementation) {}
}
