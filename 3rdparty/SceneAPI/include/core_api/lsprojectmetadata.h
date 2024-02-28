#pragma once

#include <core_api/lsattributecontainer.h>

namespace SCENE_API
{

// Forward declarations
class LSProjectMetadata_Implementation;

/// Interface to access metadata of FARO project formats.
/// \version	SCENE API version 2.0.27.
class LSProjectMetadata : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSProjectMetadata)

public:

	/// Gets the file system path to the directory of this project.
	/// \version	SCENE API version 2.0.27.
	CORE_API_EXPORT LSString getPath() const;

	/// Returns the unique id of this project.
	/// The UUID is of the windows API GUID structure type (see guiddef.h)
	/// \version	SCENE API version 2.0.27.
	CORE_API_EXPORT LSString getUuid() const;

	/// Returns the name of this project.
	/// \version	SCENE API version 2.0.27.
	CORE_API_EXPORT LSString getName() const; 
	
	/// Returns the format type of this project.
	/// Currently the following project types are supported:
	/// 'lsproj' - SCENE Project Format
	/// 'raw' - SD card format pre V9 Focus
	/// 'lsdatav2' - SD card format introduced with V9 Focus
	/// \version	SCENE API version 2.0.27.
	CORE_API_EXPORT LSString getType() const;

protected:
	LS_INTERFACE(LSProjectMetadata, LSAttributeContainer)
};

} // namespace SCENE_API
