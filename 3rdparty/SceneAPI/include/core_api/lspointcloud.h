#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lspointtypes.h>
#include <core_api/lsiterator.h>
#include <core_api/lsresult.h>

namespace SCENE_API {

// Forward declarations
class LSVolumeDefinition;
class LSSphereVolume;
class LSPointCloudRenderer;
class LSPointCloud_Implementation;

/// Interface class to access information and functionality of project
/// point clouds.
/// \version SCENE API Version 2.0.0.
class LSPointCloud : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSPointCloud)

public:
	///	Returns the internal version number of this point cloud.
	/// Version 1 is a point cloud created with SCENE 5.X
	/// Version 2 is a point cloud created with SCENE 6.0
	/// Version 3 is a point cloud created with SCENE >= 6.1 and contains point normals information
	/// \return	internal version number or -1 in case of an invalid point cloud
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT int getPointCloudVersion() const;

	///	Gets an iterator to run over all points which are part of the
	/// point cloud. The returned points are in global coordinates.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSIterator<LSPointXYZRGB> getPointCloudIterator();

	///	Gets an iterator to run over all points which are contained in
	/// a volume. The returned points are in global coordinates.
	/// \param	volume	The volume to search.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.9.
	CORE_API_EXPORT LSIterator<LSPointXYZRGB> getPointCloudIterator(const LSSphereVolume& volume) const;

	///	Gets an iterator to run over all points which are contained in
	/// a user-defined volume. The returned points are in global coordinates.
	/// \param	volume	The user-defined volume to search.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSIterator<LSPointXYZRGB> getPointCloudIterator(ref_ptr<LSVolumeDefinition> volume) const;

	///	Creates a renderer instance for this point cloud
	/// \return	The ref_ptr to the renderer instance for point clouds with internal version number greater or equal to 2
	/// \return A nullptr in case of internal point cloud version 1
	/// \return A nullptr in case no extended permissions are available.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT ref_ptr<LSPointCloudRenderer> createPointCloudRenderer() const;

	///	Determines the bounding box in global coordinates of this point cloud.
	/// \param minOut Output parameter describing the minimum of the bounding box.
	/// \param maxOut Output parameter describing the maximum of the bounding box.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void determineBoundingBox(Eigen::Vector3d& minOut, Eigen::Vector3d& maxOut) const;

	///	Retrieves the number of points of the this point cloud.
	/// \return Number of points of the point cloud
	/// \version	SCENE API Version 2.0.20.
	CORE_API_EXPORT uint64_t getNumberOfPoints() const;

	///	Gets an iterator to run over all points which are part of the
	/// point cloud and extract their normal data. 
	/// The returned points are in global coordinates.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.26.
	CORE_API_EXPORT LSIterator<LSPointXYZRGBN> getPointCloudNormalsIterator();

	///	Gets an iterator to run over all points which are contained in
	/// a volume. The returned points are in global coordinates.
	/// \param	volume	The volume to search.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.26.
	CORE_API_EXPORT LSIterator<LSPointXYZRGBN> getPointCloudNormalsIterator(const LSSphereVolume& volume) const;

	///	Gets an iterator to run over all points which are contained in
	/// a volume. The returned points are in global coordinates.
	/// \param	volume	The volume to search.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.26.
	CORE_API_EXPORT LSIterator<LSPointXYZRGBN> getPointCloudNormalsIterator(ref_ptr<LSVolumeDefinition> volume) const;

protected:
	LS_INTERFACE(LSPointCloud, LSInterface)
};

}
