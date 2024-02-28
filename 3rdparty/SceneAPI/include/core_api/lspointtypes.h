#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/iso_iec_988_1999.h>

namespace SCENE_API {

/// The LSPointXYZRGB class is the representation of a scan point with 
/// XYZ double coordinates and 24bit RGB color.
/// \version SCENE API Version 2.0.0.
struct LSPointXYZRGB
{
	double x; ///< The X position of the scan point.
	double y; ///< The Y position of the scan point.
	double z; ///< The Z position of the scan point.

	uint8_t r; ///< The red channel of the point color.
	uint8_t g; ///< The green channel of the point color.
	uint8_t b; ///< The blue channel of the point color.
};

/// The LSPointXYZFRGBA class is the representation of a scan point with 
/// XYZ float coordinates and 32bit RGBA color.
/// \version SCENE API Version 2.0.0.
struct LSPointXYZFRGBA
{
	float x; ///< The X position of the scan point.
	float y; ///< The Y position of the scan point.
	float z; ///< The Z position of the scan point.

	uint8_t r; ///< The red channel of the point color.
	uint8_t g; ///< The green channel of the point color.
	uint8_t b; ///< The blue channel of the point color.
	uint8_t a; ///< The alpha channel of the point color.
};

/// The LSPointXYZI class is the representation of a scan point with 
/// XYZ double coordinates and an float intensity value.
/// \version SCENE API Version 2.0.0.
struct LSPointXYZI
{
	double x; ///< The X position of the scan point.
	double y; ///< The Y position of the scan point.
	double z; ///< The Z position of the scan point.

	float i; ///< The intensity value of the scan point normalized to [0, 1]
};

/// The LSPointXYZN class is the representation of a scan point with
/// XYZ double coordinates and XYZ float components of the normal vector.
/// \version SCENE API Version 2.0.25.
struct LSPointXYZN
{
	double x; ///< The X position of the scan point.
	double y; ///< The Y position of the scan point.
	double z; ///< The Z position of the scan point.

	float nX; ///< The X component of the normal vector.
	float nY; ///< The Y component of the normal vector.
	float nZ; ///< The Z component of the normal vector.
};

/// The LSPointXYZRGBN is the representation of a scan point with XYZ double coordinates, 24Bit RGB color 
/// and XYZ float components of the normal vector
/// \version SCENE API Version 2.0.26.
struct LSPointXYZRGBN
{
	double x; ///< The X position of the scan point.
	double y; ///< The Y position of the scan point.
	double z; ///< The Z position of the scan point.

	uint8_t r; ///< The red channel of the point color.
	uint8_t g; ///< The green channel of the point color.
	uint8_t b; ///< The blue channel of the point color.

	float nX; ///< The X component of the normal vector.
	float nY; ///< The Y component of the normal vector.
	float nZ; ///< The Z component of the normal vector.
};

/// The LSPointSphericalRGB is the representation of a scan point with polar double coordinates and
/// 24bit RGB color. Since internal hardware knowledge is not always present, for foreign scans we
/// estimate the null point spherical coordinates by their position and nearby non-null points. The
/// provided points use the same coordinate system as the SCENE Quick-/Planar Views and may differ
/// from what you are using. 
/// \version SCENE API Version 2.0.31.
struct LSPointSphericalRGB
{
	double radius;	///< The radial distance of the point - distance to the origin.
	double phi;		///< The azimuthal angle - angle of rotation from the initial meridian plane.
	double theta;	///< The polar angle - angle with respect to the polar axis.

	uint8_t r; ///< The red channel of the point color.
	uint8_t g; ///< The green channel of the point color.
	uint8_t b; ///< The blue channel of the point color.
};

} // namespace SCENE_API
