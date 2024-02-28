#pragma once

#include <Core_API/lsinterface.h>
#include <Core_API/lsreftype.h>

namespace SCENE_API {

// Forward declarations
class LSSphereVolume_Implementation;

/// The LSSphereVolume class is the representation of a sphere 
/// with XYZ a center and a radius.
/// \version SCENE API Version 2.0.9.
class LSSphereVolume : public LSInterface
{
public:
	/// Constructs an LSSphereVolume at (x, y, z) with the given radius.
	/// \param	center	sphere center
	/// \param	radius	sphere radius
	/// \version	SCENE API Version 2.0.9.
	CORE_API_EXPORT LSSphereVolume(const Eigen::Vector3d center, const double radius);

protected:
	LS_INTERFACE(LSSphereVolume, LSInterface)
};

/// LSVolumeDefinition is the base class for user-defined volumes.
class LSVolumeDefinition : public LSRefType
{
public:
	virtual ~LSVolumeDefinition() {};

	enum IntersectResult { INSIDE, OUTSIDE, INTERSECT };

	/// Tests if and how a sphere intersects the volume.
	/// \param	center	sphere center
	/// \param	radius	sphere radius
	/// \version	SCENE API Version 2.0.14.
	virtual IntersectResult testSphere(const Eigen::Vector3d& center, double radius) = 0;

	/// Tests if a point intersects the volume.
	/// \param	point	point position
	/// \version	SCENE API Version 2.0.14.
	virtual bool testPoint(const Eigen::Vector3d& point) = 0;
};

}
