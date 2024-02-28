#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/iso_iec_988_1999.h>
#include <core_api/lsinterface.h>
#include <core_api/lsstring.h>
#include <core_api/lspod.h>

#include <Eigen/Core>

#include <vector>
#include <set>
#include <map>

namespace SCENE_API {

// Forward declarations
class LSAttribute_Implementation;

/// Storage class which may contain different common data types.
///
/// The LSAttribute class is a storage class which is able to store a single
/// value of type getType(). All types can also be serialized to strings and
/// read from strings using the toString() and fromString() methods.
///
/// <a name ="value types"></a>
/// Possible value types are:
///  - int8_t
///  - std::vector<int8_t>
///  - uint8_t
///  - std::vector<uint8_t>
///  - int16_t
///  - std::vector<int16_t>
///  - uint16_t
///  - std::vector<uint16_t>
///  - int32_t
///  - std::vector<int32_t>
///  - uint32_t
///  - std::vector<uint32_t>
///  - int64_t
///  - std::vector<int64_t>
///  - uint64_t
///  - std::vector<uint64_t>
///  - double
///  - std::vector<double>
///  - bool
///  - LSString
///  - std::vector<LSString>
///  - std::set<LSString>
///  - std::map<const LSString, LSString>
///  - std::vector<LSString>
///  - Eigen::Vector2d
///  - std::vector<Eigen::Vector2d>
///  - Eigen::Vector2f
///  - std::vector<Eigen::Vector2f>
///  - Eigen::Vector2i
///  - std::vector<Eigen::Vector2i>
///  - Eigen::Vector2ui
///  - std::vector<Eigen::Vectorus>
///  - Eigen::Vector3d
///  - std::vector<Eigen::Vector3d>
///  - Eigen::Vector3f
///  - std::vector<Eigen::Vector3f>
///  - Eigen::Vector3us
///  - std::vector<Eigen::Vector3ui>
///  - Eigen::Vector4d
///  - std::vector<Eigen::Vector4d>
///  - Eigen::Vector4f
///  - Eigen::Matrix4d
///  - std::vector<Eigen::Matrix4d>
///  - Eigen::Matrix4f
///
/// \version	SCENE API Version 2.0.0.
class LSAttribute : public LSInterface
{
public:

	/// Constructs an invalid attribute.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSAttribute();

	/// Destroys the attribute.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT virtual ~LSAttribute();

	/// Constructs a attribute containing a copy of the attribute \a 
	/// attribute.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSAttribute(const LSAttribute& attribute);

	/// Constructs an LSAttribute of the type defined by the constructor 
	/// parameter. For a list of possible value types see 
	/// <a href="#value types">value types</a>.
	/// \version	SCENE API Version 2.0.0.
	template<class T>
	LSAttribute(const T& value);

	/// Checks whether the attribute is valid.
	/// \return	true if the attribute is valid, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool isValid() const;

	/// Gets the attribute value. If the attribute value isn't of the
	/// type T a default instance of the type T will be returned. You can test 
	/// whether the attribute value is of a certain type using the hasType() 
	/// function. For a list of possible value types see 
	/// <a href="#value types">value types</a>.
	/// \return	The attribute value if it could be converted, otherwise a 
	/// default	constructed instance of the template type.
	/// \version	SCENE API Version 2.0.0.
	template<class T>
	T getValue() const;

	/// Sets the attribute value. If a value of a different type than
	/// the current attribute type is assigned the attribute type will change.
	/// For a list of possible value types see 
	/// <a href="#value types">value types</a>.
	/// \version	SCENE API Version 2.0.0.
	template<class T>
	void setValue(const T& value);

	/// Gets the attribute value as a string representation.
	/// \return	The string representation of the attribute value.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString toString() const;

	/// Sets the attribute value based on the string \a value.
	/// \return	true if the value could be set based on the given string 
	///	representation, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool fromString(LSString value);

	/// Gets the type of the attribute value.
	/// \return	The type of the attribute value.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getType() const;

	/// Checks whether the attribute value is of a given type.
	/// \return	true if the attribute value has the given type, false 
	/// otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool hasType(LSString type) const;

	/// Checks whether the attribute value is of a given type. The 
	/// template type T is used for the check. For a list of possible value 
	/// types see <a href="#value types">value types</a>.
	/// \version	SCENE API Version 2.0.0.
	template<class T>
	bool hasType() const;

	/// Assignment Operator. Assigns the value of the given attribute 
	/// to this attribute. This also sets the attribute type of this attribute 
	/// to the type of the attribute from which the values is assigned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSAttribute& operator=(const LSAttribute& from);

	/// Default allocation function. Overloaded in order to always
	/// allocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void* operator new(size_t tSize);

	/// Default deallocation function. Overloaded in order to always
	/// deallocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void  operator delete(void* p);

protected:
	template<class T> void createFrom(const T& value);

protected:
	LS_INTERFACE(LSAttribute, LSInterface)
};

//-----------------------------------------------------------------------------
#define DECLARE_LSATTRIBUTE_TYPE(T) \
	template<> CORE_API_EXPORT LSAttribute::LSAttribute(const T& value); \
	template<> CORE_API_EXPORT T LSAttribute::getValue<T>() const; \
	template<> CORE_API_EXPORT void LSAttribute::setValue<T>(const T& value); \
	template<> CORE_API_EXPORT bool LSAttribute::hasType<T>() const;

//-----------------------------------------------------------------------------
#define DECLARE_LSATTRIBUTE_POD_TYPE(T) \
	DECLARE_LSATTRIBUTE_TYPE(LSPod<T>) \
	template<> CORE_API_EXPORT void LSAttribute::createFrom<LSPod<T> >(const LSPod<T>& value); \
	template<> inline LSAttribute::LSAttribute(const T& value) : LSInterface(0) \
	{ createFrom(LSPod<T>(value)); } \
	template<> inline T LSAttribute::getValue<T>() const \
	{ return LSAttribute::getValue<LSPod<T> >().get(); } \
	template<> inline void LSAttribute::setValue<T>(const T& value) \
	{ LSAttribute::setValue<LSPod<T> >(value); } \
	template<> inline bool LSAttribute::hasType<T>() const \
	{ return LSAttribute::hasType<LSPod<T> >(); }	

// Valid attribute types
typedef std::map<const LSString, LSString> StringMap;

DECLARE_LSATTRIBUTE_TYPE(int8_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<int8_t>)
DECLARE_LSATTRIBUTE_TYPE(uint8_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<uint8_t>)
DECLARE_LSATTRIBUTE_TYPE(int16_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<int16_t>)
DECLARE_LSATTRIBUTE_TYPE(uint16_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<uint16_t>)
DECLARE_LSATTRIBUTE_TYPE(int32_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<int32_t>)
DECLARE_LSATTRIBUTE_TYPE(uint32_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<uint32_t>)
DECLARE_LSATTRIBUTE_TYPE(int64_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<int64_t>)
DECLARE_LSATTRIBUTE_TYPE(uint64_t)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<uint64_t>)
DECLARE_LSATTRIBUTE_TYPE(double)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<double>)
DECLARE_LSATTRIBUTE_TYPE(bool)
DECLARE_LSATTRIBUTE_TYPE(LSString)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<LSString>)
DECLARE_LSATTRIBUTE_POD_TYPE(std::set<LSString>)
DECLARE_LSATTRIBUTE_POD_TYPE(StringMap)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector2d)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector2d>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector2f)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector2f>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector2i)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector2i>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector2ui)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector2us>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector3d)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector3d>)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<std::vector<Eigen::Vector3d> >)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector3f)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector3f>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector3us)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector3ui>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector4d)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Vector4d>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Vector4f)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Matrix4d)
DECLARE_LSATTRIBUTE_POD_TYPE(std::vector<Eigen::Matrix4d>)
DECLARE_LSATTRIBUTE_TYPE(Eigen::Matrix4f)

}
