#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsobject.h>
#include <core_api/lsbinaryreader.h>

/// \defgroup gbo Generic Binary Objects
/// Functions and types related to the Generic Binary Object functionality

namespace SCENE_API
{
/// Interface to create and read generic binary objects.
/// Generic binary objects (GBOs) can store user-defined data inside a SCENE project.
/// GBOs are not visible in the SCENE structure tree, but behave otherwise like other SCENE objects.
/// An good example use case would be to store additional binary data that can be only understood
/// by your plugin app or standalone app inside a SCENE project to make it self-contained.
/// Please remember that older API versions might not fully support SCENE projects with GBOs.
/// GBOs can be created below many different parent objects.
/// Useful examples are the root object, clusters or scans.
/// \ingroup gbo
/// \version SCENE API version 2.0.26.
class LSGenericBinaryObject : public LSObject
{
	LS_UNCOPYABLE(LSGenericBinaryObject)

public:
	/// Returns an binary data iterator that can be used to read the binary data.
	/// The returned iterator object will have an exclusive read lock on the GBO while its alive!
	/// Make sure to free the binary data iterator as soon as possible.
	/// \see LSBinaryReader
	/// \return A nullptr in case of any unexpected errors.
	/// \version SCENE API Version 2.0.26
	CORE_API_EXPORT ref_ptr<LSBinaryReader> getData();

	/// Returns the exact overall size of the data.
	/// May be slow for large objects since it requires to stream through the data once.
	/// \version SCENE API Version 2.0.26
	CORE_API_EXPORT size_t getSize() const;

	/// Returns the MIME type string of the Generic Binary Object.
	/// See also: https://www.iana.org/assignments/media-types/media-types.xhtml
	/// \version SCENE API Version 2.0.26
	CORE_API_EXPORT LSString getMimeType() const;

	/// Returns the context string of the Generic Binary Object.
	/// The context string is user-defined and used to group the same type of objects.
	/// \version SCENE API Version 2.0.26
	CORE_API_EXPORT LSString getContext() const;

	/// Returns the ID string of the Generic Binary Object.
	/// The ID string is user-defined and used to identify objects inside the same context.
	/// \version SCENE API Version 2.0.26
	CORE_API_EXPORT LSString getId() const;

	/// Create a Generic Binary Object from a given file.
	/// The MIME type can be set automatically based on file extension.
	/// \param parent	Parent object reference.
	/// \param name		The tree object name to be set for the object.
	/// \param context	User-defined context string. Should be used to group the same type of GBOs.
	/// \param id		User-defined ID string. Should be used to identify GBOs inside the same context.
	/// \param filePath	Path to the file from which to read the data.
	/// \param gbo		Returns the new Generic Binary Object.
	/// \param mimeType	Optional MIME type. If left empty, it will be derived from the file extension.
	/// \return			LSResult::Ok The GenericBinaryObject was created successfully.
	///					LSResult::InvalidRequest Supplied an invalid or unsupported parent object.
	///					LSResult::ReadWrite Unable to read file.
	///					LSResult::Unauthorized You do not have the API key required to create Generic Binary Objects.
	/// \version SCENE API Version 2.0.26.
	CORE_API_EXPORT static LSResult::Result createGenericBinaryObject(
		const ref_ptr<LSObject>& parent,
		const LSString& name,
		const LSString& context,
		const LSString& id,
		const LSString& filePath,
		ref_ptr<LSGenericBinaryObject>& gbo,
		const LSString& mimeType = LSString()
	);

	/// Create a GenericBinaryObject from a custom data source.
	/// You need to provide a custom implementation of the LSBinaryReader interface.
	/// Please keep in mind that this implementation is not suited for very large data
	/// that does not easily fit into the computers main memory. For very big objects,
	/// we recommend to use the file based interface for creation.
	/// \param parent	The parent object reference.
	/// \param name		The name to be set for the GenericBinaryObject.
	/// \param context	User-defined context string. Should be used to group the same type of GBOs.
	/// \param id		User-defined ID string. Should be used to identify GBOs inside the same context.
	/// \param mimeType	MIME type string for the data. Example: "image/jpeg"
	/// \param source	An LSBinaryReader instance you need to implement for providing the binary data.
	/// \param gbo		Returns the new created GenericBinaryObject.
	/// \return			LSResult::Ok The GenericBinaryObject was created successfully.
	///					LSResult::InvalidRequest Supplied an invalid or unsupported parent object.
	///					LSResult::ReadWrite Unable to read the data source to the end.
	///					LSResult::Unauthorized You do not have the API key required to create Generic Binary Objects.
	/// \see LSBinaryReader
	/// \version SCENE API Version 2.0.26.
	CORE_API_EXPORT static LSResult::Result createGenericBinaryObject(
		const ref_ptr<LSObject>& parent,
		const LSString& name,
		const LSString& context,
		const LSString& id,
		const LSString& mimeType,
		const ref_ptr<LSBinaryReader>& source,
		ref_ptr<LSGenericBinaryObject>& gbo
	);

protected:
	LS_INTERFACE(LSGenericBinaryObject, LSObject)
};

} // SCENE_API
