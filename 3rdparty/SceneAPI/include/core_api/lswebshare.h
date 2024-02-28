///////////////////////////////////////////////////////////////////////////////
/// \file
///
///	Description: 
/// LSWebShare provides access to WebShare related functionality of SCENE.
///
/// COPYRIGHT (C) 2005-2017 FARO Technologies Inc., ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <core_api/lsreftype.h>
#include <core_api/lsresult.h>
#include <core_api/lsstring.h>

namespace SCENE_API {

// Forward declarations
class LSProject;
class LSWebShareSettings;
class LSLoginSettings;
class LSWebShare_Implementation;

//-----------------------------------------------------------------------------
// L S W e b S h a r e
//-----------------------------------------------------------------------------

/// Provides interfaces related to WebShare.
/// \version SCENE API Version 2.0.19.
class LSWebShare : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSWebShare)

public:
	/// Gets the folder path of the most recent WebShare Cloud export of the provided project,
	/// with a trailing backslash.
	/// \param		project Project to use.
	/// \param[out]	path Found folder path.
	///				Guaranteed to be not empty if LSResult::Ok is returned.
	///				Guaranteed to be empty if an error code is returned.
	/// \return		An LSResult result code.
	///				Ok on success
	///				InvalidRequest on project-related failures
	///				Unauthorized on missing API key
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT static LSResult::Result getWebShareDataPath(const ref_ptr<const LSProject>& project, LSString& path);

	/// Carries out a WebShare Cloud data export, including a parallel upload to a WebShare Cloud server
	/// if the login settings are provided as well.
	/// Calls the check methods of the settings objects to ensure that valid values are provided.
	/// \param project Project for which the WebShare Cloud data should be created.
	/// \param webshareSettings Export settings that specify various aspects of the data export.
	/// \param [loginSettings] Login settings for establishing a connection to a WebShare Cloud server for a parallel upload.
	/// \return	An LSResult result code.
	///         Ok on success
	///         InvalidRequest on invalid settings, invalid context state or on user-initiated cancellation of the process
	///         ReadWrite on all kinds of file operation errors
	///         DuplicateName on duplicate name errors
	///         Unauthorized on all kinds of authentication and authorization errors and missing API key
	///         Network on all kinds of server connection errors
	///         Internal on all other errors
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT static LSResult::Result createWebShareData(const ref_ptr<const LSProject>& project,
		const ref_ptr<const LSWebShareSettings>& webshareSettings, const ref_ptr<const LSLoginSettings>& loginSettings = nullptr);

protected:
	LS_INTERFACE(LSWebShare, LSInterface)
};

}
