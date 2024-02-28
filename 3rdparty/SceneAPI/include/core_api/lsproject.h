#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>
#include <core_api/lsworkspace.h>
#include <core_api/lsprojectmetadata.h>

namespace SCENE_API {

// Forward declarations
class LSProject_Implementation;

/// Interface to access information and functionality of SCENE projects.
/// \version SCENE API Version 2.0.0.
class LSProject : public LSWorkspace
{
	LS_UNCOPYABLE(LSProject)

public:

	/// Destroys the workspace.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ~LSProject();

	/// Creates a new project at the specified location.
	/// \param	projectPath	The file system path to folder where the project
	/// will be created.
	/// \param	projectName	The name of the project to be created.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSResult::Result createProject(
								LSString projectPath, 
								LSString projectName);

	/// Creates a new project at the specified location.
	/// \param	projectPath	The file system path to folder where the project
	/// will be created.
	/// \param	projectName	The name of the project to be created.
	/// \param	uuid	The UUID of the project to be created. The UUID is expected to 
	/// be of the windows API GUID structure type (guiddef.h) If the UUID is empty 
	/// a new UUID will be generated. If the provided UUID is not valid this call 
	/// will fail and return with InvalidRequest.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.25.
	CORE_API_EXPORT static LSResult::Result	createProject(
								LSString projectPath, 
								LSString projectName, 
								LSString uuid);

	/// Opens the project at the specified location.
	/// When working with the Standalone API you should also call
	/// LSStandaloneContext::setCurrentWorkspace() after successfully loading a project.
	/// A compatibility issue may occur if the project to be loaded contains objects
	/// that are only available in a newer SCENE versions. The project can still be open
	/// as 'Read-Only'.
	/// \param	projectPath	The file system path to the project folder or 
	/// project file to be loaded.
	/// \param	projectOut	Out parameter in which the project instance is
	/// provided if the workspace was successfully loaded.
	/// \param	readOnly	Whether the project should be loaded read-only.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSResult::Result loadProject(
								LSString projectPath,
								ref_ptr<LSProject>& projectOut,
								bool readOnly = false);

	/// Saves the current workspace state to a new revision within
	/// the loaded project.
	/// \param	commitMessage	The commit message for the revision.
	/// \param	author	The author of the revision.
	/// \param	updateProjectPointCloud	Whether the project point cloud should
	/// be updated during the commit.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result saveRevision(
								LSString commitMessage = L"", 
								LSString author = L"",
								bool updateProjectPointCloud = false);

	/// Gets the project name of this project
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getProjectName() const;

	/// Returns the unique id of this project.
	/// \version	SCENE API Version 2.0.25.
	CORE_API_EXPORT LSString getUuid() const;

	/// Gets the file system path to the project folder of this project.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getProjectPath() const;

	/// Gets the file system path to the project file of this project.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getProjectFilePath() const;

	/// Creates a new base revision for the loaded project. All previous revisions
	/// are either immediately deleted or marked as obsolete.
	/// Currently opened 2D views and 3D views get closed.
	/// \return	An LSResult result code.
	///         InvalidRequest is returned when there are unsaved changes.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result cleanRevisions();

	/// Scan a given path and return metadata of all contained FARO projects.
	/// This method is intended to list scan projects from Focus or Freestyle SD cards.
	/// However, it can also find and list normal SCENE projects.
	/// This method is restricted and only available with a corresponding API key.
	/// \param inputDirectory File system path to the input directory.
	/// \param recursive If True all subdirectories will be scanned recursively. Default value is true.
	/// \return	List containing metadata for all found projects. In case of any error
	/// (e.g. path does not exist or no valid API key) it will and return an empty list.
	/// \version SCENE API Version 2.0.27.
	CORE_API_EXPORT static LSPod<std::vector<ref_ptr<LSProjectMetadata>>> listScannerProjects(
		const LSString& inputDirectory,
		bool recursive = true);

	/// Import a scanner project into an existing project.
	/// The existing target project is specified by a path to the project file.
	/// The scanner project to be imported is specified by a meta data object created by \ref LSProject::listScannerProjects().
	/// This method is only intended for importing scanner projects from SD cards or USB sticks created by Freestyle and Focus devices.
	/// To import SCENE projects or workspaces use \ref LSWorkspace::importData().
	/// This method is restricted and only available with a corresponding API key.
	/// \param projectPath	File system path to the target project folder or project file. The project has to be a valid SCENE project.
	/// \param metadata	The meta data container (obtained from \ref LSProject::listScannerProjects()) defining the project to import. 
	/// \return	An LSResult result code.
	/// Without a valid API key it will fail and return Unauthorized.
	/// If the provided meta data path does not exist or if called without read permission, it will fail and return ReadWrite.
	/// If there is no project with the given meta data it will fail and and return InvalidRequest.
	/// \version SCENE API version 2.0.27.
	CORE_API_EXPORT static LSResult::Result importScannerProject(
		const LSString& projectPath,
		const ref_ptr<LSProjectMetadata>& metadata);

protected:
	LS_INTERFACE(LSProject, LSWorkspace)
};

} // namespace SCENE_API
