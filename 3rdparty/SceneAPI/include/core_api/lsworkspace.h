#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>
#include <core_api/lsinterface.h>
#include <core_api/lsstring.h>
#include <core_api/lsobject.h>
#include <core_api/lsscan.h>
#include <core_api/lspointcloud.h>
#include <core_api/lspointselection.h>
#include <core_api/lssignal.h>
#include <core_api/lsworkspaceevent.h>

namespace SCENE_API {

// Forward declarations
class LSWorkspace_Implementation;

/// Provides general access to all SCENE workspace types.
/// \version SCENE API Version 2.0.0.
class LSWorkspace : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSWorkspace)

public:

	/// Gets the root object of the workspace object tree.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSObject> getRootObject() const;

	/// Convenience function to acquire a list of all scans which are
	///			part of the object tree.
	/// \return	A list containing all scans which are part of the workspace.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSPod<std::vector<ref_ptr<LSScan> > > getScans() const;

	/// Imports data from a file into this workspace. The specified
	/// file may be of any supported scan or project type.
	/// \param	filePath	The path to the file to be imported.
	/// \return	true if the file was successfully imported, false otherwise.
	/// \version	SCENE API Version 2.0.3.
	CORE_API_EXPORT bool importData(const LSString& filePath);

	/// Gets the current list of selected objects with this workspace.
	/// \return	Al list containing all selected objects of this workspace.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSPod<std::vector<ref_ptr<LSObject> > > getSelectedObjects() const;

	/// Gets the project point cloud of this workspace.
	/// \return	The project point cloud if it exists, a nullptr otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSPointCloud> getPointCloud() const;

	/// Creates a project point cloud of all scans in that workspace.
	/// If the project contains modifications, the project must be saved before
	/// the creation is possible. Otherwise LSResult::Internal will be returned.
	/// Project must to be open with write access. Otherwise LSResult::Internal will be returned.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSResult::Result createPointCloud();

	/// Deletes the project point cloud.
	/// If the project contains modifications, the project must be saved before
	/// the deletion is possible. Otherwise LSResult::Internal will be returned.
	/// Project must to be open with write access. Otherwise LSResult::Internal will be returned.
	/// \return	An LSResult result code.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSResult::Result deletePointCloud();

	/// Gets the current spatial point selection of this workspace.
	/// \return	The current point selection if it exists, a nullptr otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSPointSelection> getPointSelection() const;

	///@name	Signals
	//@{

	/// Dispatched when the object selection has changed.
	/// \version	SCENE API Version 2.0.0.
	LSSignal<ref_ptr<LSWorkspaceEvent> > onObjectSelectionChanged;

	/// Dispatched when the point selection has changed.
	/// \version	SCENE API Version 2.0.0.
	LSSignal<ref_ptr<LSWorkspaceEvent> > onPointSelectionChanged;

	//@}

protected:
	LS_INTERFACE(LSWorkspace, LSInterface)
};

}
