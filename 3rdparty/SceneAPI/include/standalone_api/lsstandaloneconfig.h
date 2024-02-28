#pragma once

#include <core_api/lsappcontext.h>

namespace SCENE_API
{
class LSStandaloneConfig_Implementation;

/// Configuration for complete Standalone Context configuration
/// allows chaining e.g. LSStandaloneConfig{}.setLicenceKey(key).setLoggingEnabled(true)
/// \version SCENE API 2.0.32
class LSStandaloneConfig
{
	LS_UNCOPYABLE(LSStandaloneConfig);
	LSStandaloneConfig_Implementation* m_impl;

public:
	/// Default constructor yields logging disabled and no license key
	/// change configuration by using setters
	STANDALONE_API_EXPORT LSStandaloneConfig();
	STANDALONE_API_EXPORT ~LSStandaloneConfig();

	/// set API key to unlock extended functionality, e.g. registration
	/// \param licenceKey
	STANDALONE_API_EXPORT LSStandaloneConfig& setLicenseKey(LSString const& licenseKey);

	/// set loggingEnabled true to enable logging
	/// \param loggingEnabled 
	STANDALONE_API_EXPORT LSStandaloneConfig& setLoggingEnabled(bool const loggingEnabled);

	STANDALONE_API_EXPORT bool loggingEnabled() const;
	STANDALONE_API_EXPORT LSString const* licenseKey() const;
};

}
