#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>
#include <core_api/lsattributecontainer.h>
#include <core_api/lsiterator.h>
#include <core_api/lsstring.h>
#include <core_api/lsresult.h>

namespace SCENE_API {

// Forward declarations
class LSObject_Implementation;

/// Information container which can be used to build up a hierarchical tree
/// structure of container elements.
/// \version	SCENE API Version 2.0.0.
class LSObject : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSObject)

public:

	/// Calculates the transformation matrix which transforms local 
	/// object coordinates to global coordinates. 
	/// \return	The transformation matrix.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT Eigen::Matrix4d getTransformationToGlobal() const;

	/// Selects this object.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void select();

	/// Gets an iterator which can be used for a breadth-first iteration over
	/// all objects below the object in the object hierarchy.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSIterator<ref_ptr<LSObject> > getChildIterator() const;

	/// Returns the parent of this object.
	/// \return	The parent of this object.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSObject> getParent() const;

	/// Returns the number of children of this object.
	/// \return	The number of children of this object.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT unsigned int getNumChildren() const;

	/// Returns the n-th child of this object.
	/// \param	n	The position of a child of this object.
	/// \return	The n-th child of this object.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSObject> getChild(unsigned int n) const;

	/// Returns the child of this object with a given name.
	/// \param	name	The name of the object to retrieve.
	/// \return	The child child of this object which matches the given name.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSObject> getChild(LSString name) const;

	/// Removes a child from this object.
	/// \param	n	The position of the child to be removed.
	/// \return	true if the child could be removed, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool rmChild(unsigned int n);

	/// Removes a child from this object.
	/// \param	name	The name of the child to be removed.
	/// \return	true if the child could be removed, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool rmChild(LSString name);

	/// Creates a new child of the given type.
	/// \param	typeName	The type of the object to create, specified by its 
	/// class name.
	/// \param	name	The name of the child to create (The name might be
	/// automatically changed when it conflicts with another child).
	/// \param[out]	childOut	The child which has been added.
	/// \return An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result addChild(LSString name, LSString typeName, ref_ptr<LSObject>& childOut);

	/// Generates a valid and unique name for a new child of this object based on the provided base name.
	/// This name can then be used for safely calling addChild with regard to the name of the new child.
	/// \param baseName The desired name of the new child.
	/// \param[out] nameOut The generated unique name for the new child.
	/// \return An LSResult result code.
	///         In case of an error, nameOut is an empty string.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result generateUniqueChildName(const LSString& baseName, LSString& nameOut) const;

	/// Changes the parent of this object. This is equal to moving the object in the structure tree.
	/// The object must be movable.
	/// The object must support the new parent as parent.
	/// The new parent must support this object as child.
	/// The moved object will keep its global position, meaning the objects local transformation
	/// can be changed by this method. This of course only applies to objects with a 3D position.
	/// \param newParent Reference to the new parent object that should contain the object as child.
	/// \return An LSResult result code.
	/// \version	SCENE API Version 2.0.24.
	CORE_API_EXPORT LSResult::Result setParent(ref_ptr<LSObject> newParent);

protected:
	LS_INTERFACE(LSObject, LSAttributeContainer)
};


}
