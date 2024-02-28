#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lsresult.h>
#include <core_api/lsstring.h>
#include <core_api/lsattribute.h>

namespace SCENE_API {

// Forward declarations
class LSAttributeContainer_Implementation;

/// A general information container class which can contain attributes
/// of different type.
/// \version	SCENE API Version 2.0.0.
class LSAttributeContainer : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSAttributeContainer)

public:

	/// Gets the type name of this instance.
	/// For objects not known to this API version, the default type name is FallbackObject
	/// \return		The type name of this instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getTypeName() const;

	/// Gets the name of the container.
	/// \return		The name of the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getName() const;

	/// Sets the name of the container.
	/// \param	name	The name to be set for the container.
	CORE_API_EXPORT LSResult::Result setName(LSString name);

	/// Returns the unique id of the container.
	/// \return		The unique id of the container or an empty string if the 
	///				container does not yet have an id.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getUuid() const;

	/// Assigns a unique id to the container if the container does not
	/// not yet have a unique id. If a unique id is already present
	/// nothing is changed.
	/// \return		The unique id of the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString assignUuid();


	/// Get the number of attributes in the container.
	/// \return		The number of attributes in the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT unsigned int getNumAttributes() const;

	/// Get the name of an attribute in the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getAttributeName(unsigned int index) const;

	/// Get the index of an attribute in the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT unsigned int getAttributeIndex(LSString name) const;

	/// Get an attribute based on its index. 
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSAttribute getAttribute(unsigned int index) const;

	/// Get an attribute based on its name. 
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSAttribute getAttribute(LSString name) const;

	/// Set an attribute based on its index.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result setAttribute(unsigned int index, const LSAttribute& attribute);

	/// Set an attribute based on its name.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result setAttribute(LSString name, const LSAttribute& attribute);

	/// Add a new custom attribute to the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result addCustomAttribute(LSString name, const LSAttribute& attribute);

	/// Remove a custom attribute from the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool removeCustomAttribute(LSString name);


	/// Returns the number of fields in the container.
	/// \return	The number of fields in the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT unsigned int getNumFields() const;

	/// Returns the field at position n in the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSAttributeContainer> getField(unsigned int index) const;

	/// Returns the field with the given name.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSAttributeContainer> getField(const LSString& name) const;

	/// Add a field to the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result addField(const LSString& name, const LSString& typeName, ref_ptr<LSAttributeContainer>& fieldOut);

	/// Removes the field with a given name from the container.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool rmField(const LSString& name);


	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT friend bool operator==(const LSAttributeContainer& container1, const LSAttributeContainer& container2);
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT friend bool operator!=(const LSAttributeContainer& container1, const LSAttributeContainer& container2);

protected:
	LS_INTERFACE(LSAttributeContainer, LSInterface)
};

}
