#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>
#include <core_api/lsworkspace.h>


namespace SCENE_API {

// Forward declarations
class LSLocalWorkspace_Implementation;

/// Interface to access information and functionality of local workspaces.
/// \version SCENE API Version 2.0.0.
class LSLocalWorkspace : public LSWorkspace
{
	LS_UNCOPYABLE(LSLocalWorkspace)

public:

	/// Destroys the workspace.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ~LSLocalWorkspace();

	/// Loads a local workspace from the file system.
	/// When working with the Standalone API you should also call
	/// LSStandaloneContext::setCurrentWorkspace() after successfully loading a project.
	/// \param	workspacePath	The file system path to the workspace file to 
	/// be loaded.
	/// \param	workspaceOut	Out parameter in which the workspace instance
	/// is provided if the workspace was successfully loaded.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSResult::Result loadWorkspace(
								LSString workspacePath,
								ref_ptr<LSLocalWorkspace>& workspaceOut);

	/// Saves the current workspace state back to the local workspace file.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result saveWorkspace();

protected:
	LS_INTERFACE(LSLocalWorkspace, LSWorkspace)
};

}
