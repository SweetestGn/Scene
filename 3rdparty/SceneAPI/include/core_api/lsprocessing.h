#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsscan.h>
#include <core_api/lsprocesssettings.h>


/// \defgroup processing Processing
/// Functions and types related to the processing functionality

/// \defgroup registration Registration
///Functions and types related to the registration functionality


namespace SCENE_API {

/// Enumeration for the different registration types.
/// \ingroup registration
enum RegistrationMethod {
	RM_CloudToCloud, ///< Cloud to cloud registration.
	RM_TopViewBased, ///< Top view / projection based registration.
	RM_TargetBased ///< Target based Registration.
};

/// Registers a scan against a reference scan. Only the scan to register will be moved not the
/// reference scan.
/// \param referenceScan			The scan to which the other scan is registered
/// \param scanToRegister			The scan to register. 
/// \param registrationMethod		The registration method to use. E.g. CLOUD_TO_CLOUD
/// \param registrationSuccessful	Out parameter describing whether the registration was successful
/// \ingroup						registration
/// \version						SCENE API Version 2.0.5.
CORE_API_EXPORT LSResult::Result registerScan(LSScan& referenceScan,
											  LSScan& scanToRegister,
											  RegistrationMethod registrationMethod,
											  bool& registrationSuccessful);

/// Registers scan against the global references of the project.
/// \param scanToRegister			The scan to register. 
/// \param registrationSuccessful	Out parameter describing whether the registration was successful
/// \ingroup						registration
/// \version						SCENE API Version 2.0.9.
CORE_API_EXPORT LSResult::Result registerScanWithReferences(LSScan& scanToRegister,
															bool& registrationSuccessful);


/// Registers all scans belonging to the cluster
/// \param clusterToRegister		The cluster to register
/// \param registrationMethod		The registration method to use. E.g. RM_CloudToCloud
/// \param registrationSuccessful	Out parameter describing whether the registration was successful
/// \ingroup						registration
/// \version						SCENE API Version 2.0.10.
CORE_API_EXPORT LSResult::Result registerCluster(LSObject& clusterToRegister,
												RegistrationMethod registrationMethod,
												bool& registrationSuccessful);

/// Processes the scan with some default processing settings.
/// This will colorize the scan and create a scan point cloud.
/// \param scan					The scan to process.
/// \param forceProcessing		Flag to force processing even if already processed
/// \return						LSResult::Ok Processing was successful.
///								LSResult::InvalidRequest The supplied parameters are wrong or the project needs to be saved first.
///								LSResult::Unauthorized You do not have the API key required to process scans in general or this specific scan type.
/// \ingroup					processing
/// \version					SCENE API Version 2.0.5.
CORE_API_EXPORT LSResult::Result processScan(LSScan& scan,
											 bool forceProcessing = false);

/// Processes the scan with some default processing settings.
/// This will colorize the scan and create a scan point cloud. 
/// \param scan				The scan to process.
/// \param settings			Processing options
/// \param forceProcessing	Flag to force processing even if already processed
/// \return					LSResult::Ok Processing was successful.
///							LSResult::InvalidRequest The supplied parameters are wrong or the project needs to be saved first.
///							LSResult::Unauthorized You do not have the API key required to process scans in general or this specific scan type.
/// \ingroup				processing
/// \version				SCENE API Version 2.0.19.
CORE_API_EXPORT LSResult::Result processScan(LSScan& scan,
											 const ref_ptr<LSProcessSettings>& settings,
											 bool forceProcessing = false);

/// Preprocess an object.
/// Preprocess is required for some tree objects before they can be properly used.
/// Two examples are Swift Sequences which need trajectory calculation and internal registration before they become usable,
/// and PanoCam scans which first need a calibration to be calculated before colorization can be performed. If any non-Swift Sequence
/// is provided, including the root object, it and all of its children are searched for PanoCam scans and all those found
/// will be preprocessed as such.
/// \param objectToPreprocess	The object which needs preprocessing.
/// \return						LSResult::Ok Preprocessing was successful.
///								LSResult::InvalidRequest The supplied parameters are wrong.
///								E.g. The object type has no associated preprocessing operation.
///								LSResult::Unauthorized You do not have the API key required for preprocessing this object.
///								Different object types might require different API key permissions!
/// \ingroup					processing
/// \version					SCENE API Version 2.0.22.
CORE_API_EXPORT LSResult::Result preprocessObject(LSObject& objectToPreprocess);

/// Creates a panorama image that can be larger than the resolution of the scan.
/// The pixels in the panorama image have equal angular distance to each other.
/// Pixel top left pixels equals 0 degrees both vertically to horizontally.
/// Bottom right Pixel equals 360 degrees horizontally and 180 degrees vertically.
/// The area with more than 150 vertical degrees will be empty for FARO laser scans.
/// The resulting image file will be written to the specified output folder.
/// The filename will be {scanname}.{format} (e.g. "scan123.jpg").
/// Make sure the scan is loaded before calling this method.
/// \param scan					The scan the image should be created for.
/// \param outputPath			The output folder for the generated image file.
/// \param fullColorDetail		Create a panorama that uses the full color data independent of the scan's resolution.
/// \param createLDRImages		Also creates a panorama image for each exposure time if the scan has HDR.
///								The filenames will look like scan123_LDR_1.jpg, scan123_LDR_2.jpg, ...
///								Currently this option only works if fullColorDetail is set to true.
/// \param doNotCreateHDRImage	Skip generation of the tone mapped HDR panorama.
///								This is useful to save time if you are only interested in the LDR images.
/// \param format				The output format as string. Supported formats are "png", "bmp" and "jpg".
/// \param backgroundColor		The background color is used to fill areas where there is no scan data.
///								It is a hex color code in RGB order. E.g. 0xFF0000 is red.
///								Alpha channel is not supported.
/// \ingroup					processing
/// \version					SCENE API Version 2.1.0.
CORE_API_EXPORT LSResult::Result createCompensatedPanoramaImage(
	LSScan& scan, 
	const LSString& outputPath = L".\\",
	const bool fullColorDetail = false,
	const bool createLDRImages = false,
	const bool doNotCreateHDRImage = false,
	const LSString& format = L"jpg",
	const uint32_t backgroundColor = 0xFFFFFF);

/// DEPRECATED. See createCompensatedPanoramaImage
/// \version					SCENE API Version 2.0.18.
CORE_API_EXPORT LSResult::Result createCompensatedPanormaImage(
	LSScan& scan,
	const LSString& outputPath = L".\\",
	const bool fullColorDetail = false,
	const bool createLDRImages = false,
	const bool doNotCreateHDRImage = false,
	const LSString& format = L"jpg",
	const uint32_t backgroundColor = 0xFFFFFF);

/// Colorizes the scan.
/// Colorization is normally done during the processing of a scan. However, this method permits to colorize the
/// scan without having to process it. Only FARO scans are supported.
/// \param scan:					The scan to colorize
/// \param laserIlluminatedHDR:		Will enable colorization using Laser Illuminated HDR if set to true and 
/// 								the scan supports this feature.
/// \return							LSResult::Ok if colorization run sucessfuly or if the scan has no pictures to process
/// \ingroup						processing
/// \version						SCENE API Version 2.0.20.
CORE_API_EXPORT LSResult::Result colorizeScan(LSScan& scan, const bool laserIlluminatedHDR = false);

} // namespace SCENE_API
