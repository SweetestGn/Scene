#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lspointtypes.h>
#include <core_api/lsiterator.h>
#include <core_api/lsresult.h>

namespace SCENE_API {

// Forward declarations
class LSPointCloudRenderer_Implementation;

/// Interface class to perform rendering of a point cloud
/// \version SCENE API Version 2.0.0.
class LSPointCloudRenderer : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSPointCloudRenderer)

public:

	/// Sets the resolution of the framebuffer of this renderer.
	/// Order of parameters is first x dimension, then y dimension.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void setResolution(uint16_t resolution[2]);

	/// Retrieves currently configured framebuffer resolution.
	/// Order of parameters is first x dimension, then y dimension.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void getResolution(uint16_t resolution[2]) const;

	/// Activates perspective projection and sets the horizontal field of view (in radians).
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void setPerspectiveCamera(double horizontalFOV);

	/// Returns the horizontal field of view in radians.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT double getPerspectiveFieldOfView() const;

	/// Activates orthographic projection and sets the horizontal view range (in meters) of the view.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void setOrthographicCamera(double horizontalRange);

	/// Returns the horizontal range (in meters) of the view for orthographic projection.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT double getOrthographicViewRange() const;

	/// Retrieves the near and far distance of the renderer camera.
	/// \param[out]	nearDist Output parameter for the near distance.
	/// \param[out]	farDist Output parameter for the far distance.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void getNearFar(double &nearDist, double &farDist) const;

	/// Sets the near and far distance of the renderer camera.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT void setNearFar(double nearDist, double farDist);

	/// Returns whether perspective (true) or orthographic (false) projection is active.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT bool getPerspectiveProjection() const;

	/// Determines the visible points of this point cloud under the given camera configuration.
	/// \param	cameraPos		camera position in global coordinates
	/// \param	cameraYAxis		camera up vector in global coordinates
	/// \param	cameraZAxis		camera NEGATIVE viewing direction vector in global coordinates
	/// \param	visiblePoints	address of buffer of resulting visible points in right-handed
	///							coordinate system defined by position, y axis and z axis.
	/// \param	numPoints		number of detected visible points
	/// \param	final			true if the rendering is final, false if further calls might
	///							reveal more points because not yet all points have been loaded.
	/// \version				SCENE API Version 2.0.14.
	CORE_API_EXPORT void queryVisiblePoints(
		const Eigen::Vector3d &cameraPos,
		const Eigen::Vector3d &cameraYAxis,
		const Eigen::Vector3d &cameraZAxis,
		LSPointXYZFRGBA **visiblePoints,
		size_t &numPoints,
		bool &final);

protected:
	LS_INTERFACE(LSPointCloudRenderer, LSInterface)
};

}
