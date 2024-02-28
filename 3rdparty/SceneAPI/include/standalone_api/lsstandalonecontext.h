#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsappcontext.h>

namespace SCENE_API {

// Forward declarations
class LSWorkspace;
class LSStandaloneContext_Implementation;
class LSStandaloneConfig;

/// Context class for standalone apps. Standalone apps should create a single
/// LSStandaloneContext instance before accessing ANY API functionality
/// and keep this context alive at least as long as any other API object.
/// NEVER create multiple contexts in the same process. This is not supported.
/// Avoid creating multiple sequential contexts in the same process.
/// This is known to cause problems and is also not supported officially.
/// \version Added in SCENE API Version 2.0.0.
class LSStandaloneContext : public LSAppContext
{
public:
	/// Constructor
	/// Default constructor for use cases without an API key.
	/// \version SCENE API Version 2.0.0
	STANDALONE_API_EXPORT LSStandaloneContext();

	/// Constructor
	/// \param key Key to unlock extended functionality, e.g. registration
	/// \version SCENE API Version 2.0.10
	STANDALONE_API_EXPORT LSStandaloneContext(LSString key);

	/// \param config Complete Context configuration (default equal to default ctor)
	/// \version SCENE API 2.0.31
	STANDALONE_API_EXPORT LSStandaloneContext(LSStandaloneConfig const& config);
	
	STANDALONE_API_EXPORT ~LSStandaloneContext();

	/// Sets a default workspace as is required by some operations.
	/// \param workspace The workspace to become default.
	/// \version SCENE API Version 2.0.14
	STANDALONE_API_EXPORT LSResult::Result setCurrentWorkspace(ref_ptr<LSWorkspace> workspace);

protected:
	LS_INTERFACE(LSStandaloneContext, LSAppContext)
private:
	LS_UNCOPYABLE(LSStandaloneContext)
};

}
