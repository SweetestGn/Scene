#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsevent.h>
#include <core_api/ref_ptr.h>

namespace SCENE_API {

// Forward declarations
class LSWorkspace;

/// The LSWorkspaceEvent class represents events associated to a 
/// specific workspace.
/// \version SCENE API Version 2.0.0.
class LSWorkspaceEvent : public LSEvent
{
public:
	/// Constructor. 
	/// \param	workspace	The workspace for which the event was triggered.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSWorkspaceEvent(ref_ptr<LSWorkspace> workspace);

	/// Gets the workspace instance for which the event is triggered. 
	/// \return	The task instance. 
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<LSWorkspace> getWorkspace() const;

protected:
	// The workspace for which the event was triggered.
	const ref_ptr<LSWorkspace> m_workspace;
};

}
