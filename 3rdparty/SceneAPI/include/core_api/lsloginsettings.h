#pragma once

#include <core_api/lsattributecontainer.h>

namespace SCENE_API {

// Forward declarations
class LSLoginSettings_Implementation;

//-----------------------------------------------------------------------------
// L S L o g i n S e t t i n g s
//-----------------------------------------------------------------------------

/// Container collecting settings for logging in on a server, in particular a WebShare Cloud server
/// for uploading (or downloading) WebShare data.
/// All set methods return if setting the value was successful.
/// \version SCENE API Version 2.0.19.
class LSLoginSettings : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSLoginSettings)

public:
	/// Available attributes.
	/// See the set methods below for default values and valid value ranges.
	static const LSString ATTR_SUBDOMAIN;
	static const LSString ATTR_DOMAIN;
	static const LSString ATTR_USER_NAME;
	static const LSString ATTR_USER_PASSWORD;

public:
	/// \return A new instance of the implementation class. The constructor can't be called directly.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT static ref_ptr<LSLoginSettings> create();

	/// Sets the subdomain of the server, e.g. L"preview".
	/// The URL is constructed like this: https://[subdomain].[domain]
	/// An arbitrary domain can be provided with the bracket notation:
	/// L"{https://my.example.com/?login}"
	/// In this case, the domain attribute is disregarded and can be left empty.
	/// The bracket notation is part of the subdomain instead of the domain for historical reasons.
	/// Default value = L"".
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setSubdomain(const LSString& subdomain);
	/// Sets the domain of the server, e.g. L"websharecloud.com".
	/// See the description of the subdomain attribute.
	/// Default value = L"".
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setDomain(const LSString& domain);
	/// Sets the user login name.
	/// This method must be called before connecting to the server since the default value L"" is invalid.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setUserName(const LSString& userName);
	/// Sets the user password.
	/// This method must be called before connecting to the server since the default value L"" is invalid.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setUserPassword(const LSString& userPassword);

	/// Carries out a complete check of all attributes. This includes a consistency check involving several attributes,
	/// e.g. that not both subdomain and domain are empty.
	/// \return	true if all provided settings are valid and consistent.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool check() const;

protected:
	LS_INTERFACE(LSLoginSettings, LSAttributeContainer)
};

}
