#pragma once

#include <core_api/lsobject.h>

namespace SCENE_API {

// Forward declarations
class LSProject;
class LSWebShareSettings_Implementation;

//-----------------------------------------------------------------------------
// L S W e b S h a r e S e t t i n g s
//-----------------------------------------------------------------------------

/// Container collecting settings for the WebShare Cloud data export.
/// All set methods return if setting the value was successful.
/// \version SCENE API Version 2.0.19.
class LSWebShareSettings : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSWebShareSettings)

public:
	/// Enumeration for the map type.
	enum MAP_TYPE : uint8_t {
		MT_STANDARD,
		MT_CLEAR,
		MT_GAP_FILLED,
		MT_SCENE
	};

	// Enumeration for the progress bar type.
	enum PROGRESS_TYPE : uint8_t {
		PT_NONE,
		PT_DEFAULT
	};

public:
	/// \return A new instance of the implementation class. The constructor can't be called directly.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT static ref_ptr<LSWebShareSettings> create();

	/// Sets the following settings based on the properties of the provided SCENE project:
	/// ID, Display name, Description, Keywords, Latitude, Longitude, Preview image path.
	/// \return true if all settings could be set.
	///         Either all attributes get set correctly or none, since the checks are carried out before setting the attributes.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setStandardProjectSettings(const ref_ptr<const LSProject>& project);

	/// Sets the folder path where the WebShare Cloud data should be created.
	/// Default value = L"". In this case, the standard export folder in the project's revision folder is used.
	/// If the directory already exists, it must be empty.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setDataDirectory(const LSString& dataDirectory);
	/// Sets the map type of the overview map.
	/// !!!!! Standalone apps currently only support the MAP_TYPE::MT_SCENE map type !!!!!
	/// Other map types are not supported since standalone apps can't open a 3D view.
	/// If the map type is set to MAP_TYPE::MT_SCENE, applyClippingBoxes must be false and layerBoxes must be empty
	/// since that map type does not support clipping boxes currently.
	/// Default value = MAP_TYPE::MT_SCENE.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setMapType(const MAP_TYPE type);
	/// Sets the background color of the overview map.
	/// Not used by the map type MAP_TYPE::MT_SCENE.
	/// The provided RGB values must be in the [0 to 1] interval with [0,0,0] as black and [1,1,1] as white.
	/// Default value = [1,1,1] (white).
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setMapBackgroundColor(const double r, const double g, const double b);
	/// Sets the foreground color of the overview map.
	/// Only used by the map type MAP_TYPE::MT_SCENE.
	/// The provided RGB values must be in the [0 to 1] interval with [0,0,0] as black and [1,1,1] as white.
	/// Default value = [0,0,0] (black).
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setMapForegroundColor(const double r, const double g, const double b);
	/// Adds a clipping boxes to be used for a multilayer overview map.
	/// If none is provided, the whole map will be created in a single map layer.
	/// Currently, only clipping boxes with the ClippingMode 0 (keep inside) are allowed.
	/// Call this method multiple times for different layout boxes.
	/// You may not add layer boxes to a map of type MAP_TYPE::MT_SCENE since that map type does not support clipping boxes currently.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool addLayerBox(const ref_ptr<const LSObject>& layerBox);
	/// Adds a layout plan to be used as additional map layers for the overview map.
	/// \return	true if the provided setting is valid.
	/// Call this method multiple times for different layout plans.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool addLayoutPlan(const ref_ptr<const LSObject>& layoutPlan);
	/// Sets that clipping boxes should be applied to a single map layer overview map.
	/// You may not set this value to true for a map of type MAP_TYPE::MT_SCENE since that map type does not support clipping boxes currently.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setApplyClippingBoxes(const bool applyClippingBoxes);
	/// Sets that overlay map layers for each scan should be created.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setCreateScanOverlays(const bool createScanOverlays);
	/// Sets that HD versions (8192 pixels) of the panorama images should be created 
	/// if the individual scans are large enough.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setExportHdPanorama(const bool exportHdPanorama);
	/// Sets that HD versions (8192 pixels) of the distance images should be created 
	/// if the individual scans are large enough.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setExportHdDistance(const bool exportHdDistance);
	/// Sets that the colorized versions of the panorama images should be created
	/// if the individual scan is available in color.
	/// At least one of exportColor and exportGray must be true.
	/// Default value = true.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setExportColor(const bool exportColor);
	/// Sets that the gray scale versions of the panorama images should be created
	/// if the reflection values of the individual scan are available.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setExportGray(const bool exportGray);
	/// Sets the project identifier.
	/// This method must be called before starting the export since the default value L"" is invalid.
	/// All characters must be in [a-z0-9-] and the maximal length is 40 characters.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setId(const LSString& id);
	/// Sets the project display name.
	/// The maximal length is 60 bytes.
	/// This method must be called before starting the export since the default value L"" is invalid.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setDisplayName(const LSString& displayName);
	/// Sets the project description.
	/// The maximal length is 65535 bytes.
	/// Default value = L"".
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setDescription(const LSString& description);
	/// Sets the project keywords in the form of a comma separated string of keywords, e.g. L"factory, house, power station".
	/// The maximal length is 255 bytes.
	/// Default value = L"".
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setKeywords(const LSString& keywords);
	/// Sets the latitude of the project on Earth.
	/// The provided value must be in the range [-90 to 90].
	/// Default value = 0.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setLatitude(const double latitude);
	/// Sets the longitude of the project on Earth.
	/// The provided value must be in the range [-180 to 180].
	/// Default value = 0.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setLongitude(const double longitude);
	/// Sets the file path to the project preview image.
	/// Default value = L"". In this case, one of the panorama images will be used as project image.
	/// Otherwise, the file path must point to a valid file.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setImagePath(const LSString& imagePath);
	/// Sets that the project should be flagged as public.
	/// This setting is not used by the SCENE 2go viewer.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setIsPublic(const bool isPublic);
	/// Sets that the project should be flagged as featured and be shown in the feature box.
	/// Default value = false.
	/// \return	Always true.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setFeatured(const bool featured);
	/// Sets the type of the progress information.
	/// PROGRESS_TYPE::PT_NONE = No progress information in any case.
	/// PROGRESS_TYPE::PT_DEFAULT = Display the default progress information for the app type:
	///                             Normal SCENE progress bar for plugin apps.
	///                             No progress bar for standalone apps.
	/// Default value = PROGRESS_TYPE::PT_DEFAULT.
	/// \return	true if the provided setting is valid.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool setProgressType(const PROGRESS_TYPE type);

	/// Carries out a complete check of all attributes. This includes a consistency check involving several attributes,
	/// e.g. that at least one of exportColor and exportGray is set to true.
	/// \return	true if all provided settings are valid and consistent.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT bool check() const;

protected:
	LS_INTERFACE(LSWebShareSettings, LSAttributeContainer)
};

}
