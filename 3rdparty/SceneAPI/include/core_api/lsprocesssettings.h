#pragma once

#include <core_api/lsattributecontainer.h>

namespace SCENE_API
{
// Forward declarations
class LSProcessSettings_Implementation;

/// Interface to read and write settings for processing.
/// An LSProcessSettings object can be used as additional parameter for processScan() to specify the processing settings.
/// \version SCENE API Version 2.0.19.
class LSProcessSettings : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSProcessSettings)
public:

	/// Options for the colorization of scans.
	enum class Colorization : uint8_t
	{
		NO_COLORIZATION,			///< If enabled, the scan will not be colorized
		COLORIZE_SCANS,				///< Default - Applies the image data taken by the laser scanner to colorize the scan points
		LASER_ILUMINATED_HDR		///< Enhances the color image with laser light intensity measurements.
	};

public:
	/// Creates a new settings object based on a copy of the current SCENE settings.
	/// This instance can then be used as a parameter when running processScan().
	/// \return		the created instance of LSProcessSettings.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT static ref_ptr<LSProcessSettings> create();

	/// The dark scan point filter removes points based on a minimum reflectance value.
	/// \param		filterState
	/// - true	= Filter active
	/// - false = Filter inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setDarkScanPointFilter(const bool filterState);

	/// Get the state of dark scan point filter.
	/// For more information please see setDarkScanPointFilter().
	CORE_API_EXPORT bool getDarkScanPointFilter() const;

	/// The reflectance threshold value indicates the minimum reflectance value a scan point must have.
	/// \param		reflectance Minimum reflectance value
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note		The valid Reflectance Threshold range is 0 - 2048.
	/// \note		Dark scan point filter must be active in order to take effect
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setFilterReflectanceThreshold(const int reflectance);

	/// Get reflectance threshold.
	/// For more information please see setFilterReflectanceThreshold().
	CORE_API_EXPORT int getFilterReflectanceThreshold() const;

	/// During processing, it is possible to apply color to each point based on the pictures taken by the scanner.
	/// \param		colorization Enum containing the method of colorization.
	/// \see		Colorization
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setColorization(Colorization colorization);

	/// Get colorization method.
	/// For more information please see setColorization().
	CORE_API_EXPORT Colorization getColorization() const;

	/// The distance filter simply removes scan points which are outside of a distance 
	/// range which is defined by the minimum and maximum distance.
	/// \param		filterState
	/// - true	= Filter active
	/// - false = Filter inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setDistanceFilter(const bool filterState);

	/// Get the state of distance filter.
	/// For more information please see setDistanceFilter().
	CORE_API_EXPORT bool getDistanceFilter() const;

	/// Specify the minimum distance in meters for the distance filter.
	/// For more information please see setDistanceFilter().
	/// \param		distanceValue Minimum distance in meters
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note	Distance Filter must be active in order to take effect
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setFilterMinimumDistance(const double distanceValue);

	/// Get minimum distance in meters.
	/// For more information please see setFilterMinimumDistance().
	CORE_API_EXPORT double getFilterMinimumDistance() const;

	/// Specify the maximum distance in meters of the distance filter.
	/// For more information please see setDistanceFilter().
	/// \param		distanceValue Maximum distance in meters
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note	Distance Filter must be active in order to take effect
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setFilterMaximumDistance(const double distanceValue);

	/// Get maximum distance in meters.
	/// For more information please see setFilterMinimumDistance().
	CORE_API_EXPORT double getFilterMaximumDistance() const;

	/// The edge artifact filter is especially  useful to remove artifacts at the edges of objects.
	/// \param		filterState
	/// - true	= Filter active
	/// - false = Filter inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setEdgeArtifactFilter(const bool filterState);

	/// Get the state of Edge Artifact Filter.
	/// For more information please see setEdgeArtifactFilter().
	CORE_API_EXPORT bool getEdgeArtifactFilter() const;

	/// The Stray Point Filter checks if the 2D grid cell of a scan point contains 
	/// a sufficient percentage of points with a distance similar to the scan point
	/// itself.
	/// \param		filterState
	/// - true	= Filter active
	/// - false = Filter inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setStrayFilter(const bool filterState);

	/// Get the state of Stray Point Filter.
	/// For more information please see setStrayFilter().
	CORE_API_EXPORT bool getStrayFilter() const;

	/// The size of the surrounding area used for comparison. For each scan point 
	/// of the scan the filter takes the valid scan points of this 
	/// surrounding area and counts how many of them are at a distance to the 
	/// scanner which is approximately the same as the distance of the scan point
	/// currently being checked.
	/// For more information please see setStrayFilter().
	/// \param		gridSize Size of grid
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note		The Grid size must be a positive value
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setStrayFilterGridSize(const int gridSize);

	/// Get the Size of grid.
	/// For more information please see setStrayFilterGridSize().
	CORE_API_EXPORT int getStrayFilterGridSize() const;

	/// A scan point is counted if the difference in distance is smaller than the 
	/// Distance Threshold.
	/// For more information please see setStrayFilter().
	/// \param		strayDistance Distance in meters
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note		The Distance must be a positive value
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setStrayFilterDistance(const double strayDistance);

	/// Get the Stray Distance.
	/// For more information please see setStrayFilterDistance().
	CORE_API_EXPORT double getStrayFilterDistance() const;

	/// If at least the percentage of scan points indicated by the Allocation Threshold 
	/// in the surrounding area is also within this distance threshold, the scan point
	/// remains in the scan. Otherwise it is removed.
	/// For more information please see setStrayFilter().
	/// \param		allocationPercentage Percentage of scan points
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note		The Percentage range is 0 to 1.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setStrayFilterAllocation(const double allocationPercentage);

	/// Get the Allocation Threshold.
	/// For more information please see setStrayFilterAllocation().
	CORE_API_EXPORT double getStrayFilterAllocation() const;

	/// SCENE can find spheres in the scans during processing.
	/// \param		filterState
	/// - true	= Search active
	/// - false = Search inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setSphereDetection(const bool filterState);

	/// Get the state of sphere detection.
	/// For more information please see setSphereDetection().
	CORE_API_EXPORT bool getSphereDetection() const;

	/// Set the list of active sphere radii in meters.The active sphere radii 
	/// are used during processing when searching for spheres is active.
	/// For more information please see setSphereDetection().
	/// \param		radiiVector Vector of double values corresponding to the radii of active spheres
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \note		Vector has to have at least one non negative radius.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setActiveSphereRadii(const std::vector<double>& radiiVector);

	/// Get the list of active sphere radii in meters.
	/// For more information please see setActiveSphereRadii().
	CORE_API_EXPORT std::vector<double> getActiveSphereRadii() const;

	/// SCENE can find checkerboard targets in the scans during processing.
	/// \param		filterState
	/// - true	= Search active
	/// - false = Search inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setCheckboardsDetection(const bool filterState);

	/// Get the state of checkerboard target detection.
	/// For more information please see setCheckboardsDetection().
	CORE_API_EXPORT bool getCheckboardsDetection() const;

	/// SCENE can find planes in the scans during processing.
	/// \param		filterState
	/// - true	= Search active
	/// - false = Search inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setPlaneDetection(const bool filterState);

	/// Get the state of planes detection.
	/// For more information please see setPlaneDetection().
	CORE_API_EXPORT bool getPlaneDetection() const;

	/// SCENE can find Freestyle markers in the scans during processing.
	/// \param		filterState
	/// - true	= Search active
	/// - false = Search inactive
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setMarkerDetection(const bool filterState);

	/// Get the state of Freestyle marker detection.
	/// For more information please see setMarkerDetection().
	CORE_API_EXPORT bool getMarkerDetection() const;

	/// If enabled, a scan point cloud for each scan will be created as last part of the processing.
	/// \param		creationState
	/// - true	= Create point cloud
	/// - false = Does not create point cloud
	/// \return		LSResult::Ok if the input value is valid, LSResult::InvalidRequest otherwise.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setCreatePointClouds(const bool creationState);

	/// Get the state of point cloud creation.
	/// For more information please see setCreatePointClouds().
	CORE_API_EXPORT bool getCreatePointClouds() const;

protected:
	LS_INTERFACE(LSProcessSettings, LSAttributeContainer)
};

}
