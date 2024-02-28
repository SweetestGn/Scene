#pragma once

#include <core_api/lsobject.h>

namespace SCENE_API {

// Forward declarations
class LSLayoutPlan_Implementation;

/**
* Interface to access information and functionality of layout plans.
* \version SCENE API version 2.0.19.
*/
class LSLayoutPlan : public LSObject
{
	LS_UNCOPYABLE(LSLayoutPlan)

public:
	/// Creates a new instance of the implementation class. The constructor can't be called directly.
	/// The created LayoutPlan object is also added to the SCENE object tree as child of the "LayoutPlans" folder.
	/// \param baseName Desired name for the new LayoutPlan object in the workspace tree.
	///        Is automatically adjusted if necessary to make it valid and unique.
	/// \param root SCENE workspace root.
	/// \param[out] layoutPlanOut Created layout plan object.
	/// \return An LSResult result code.
	///         In case of an error, layoutPlanOut is null.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT static LSResult::Result create(const LSString& baseName, const ref_ptr<LSObject>& root, ref_ptr<LSLayoutPlan>& layoutPlanOut);

	/// Sets and loads the image associated with the layout plan.
	/// \param imgPath File path to the image.
	/// \return An LSResult result code.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setImagePath(const LSString& imgPath);

	/// Sets the center point of the layout plan in the global coordinate system.
	/// \param centerGlobal Center point in global coordinates. Unit = meter.
	/// \return An LSResult result code.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setCenterPosition(const Eigen::Vector3d& centerGlobal);

	/// Sets the size of the layout plan so that its width and length are equal to the provided values.
	/// \param width New width (length in x direction) of the layout plan. Unit = meter.
	/// \param length New length (length in y direction) of the layout plan. Unit = meter.
	/// \return An LSResult result code.
	/// \version SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setSize(const double width, const double length);

	/// Sets the rotation of the layout plan in the global coordinate system.
	/// The Rotation is defined in radians in the global coordinate system.
	/// The rotation direction for positive angles from a top view perspective on the layout plan is:\n
	/// x: Top edge rotates towards the camera.\n
	/// y: Left edge rotates towards the camera.\n
	/// z: Top edge rotates to the left (counter-clockwise).\n
	/// This corresponds to the rotation direction of the rotation input fields in SCENE's property dialog.
	/// If multiple angles are given, the rotation order is the same as given: first x, then y, then z.
	/// Usually, one only wants to rotate around the Z axis, e.g. 90 degree counter-clockwise: [0., 0., PI/2].
	/// \param		rotXGlobal Rotation around X axis
	/// \param		rotYGlobal Rotation around Y axis
	/// \param		rotZGlobal Rotation around Z axis
	/// \return		An LSResult result code.
	/// \version	SCENE API Version 2.0.19.
	CORE_API_EXPORT LSResult::Result setRotation(const double rotXGlobal, const double rotYGlobal, const double rotZGlobal);

protected:
	LS_INTERFACE(LSLayoutPlan, LSObject)
};

}
