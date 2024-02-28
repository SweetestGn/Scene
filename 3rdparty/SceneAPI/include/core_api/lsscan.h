#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/ref_ptr.h>
#include <core_api/lsobject.h>
#include <core_api/lspointtypes.h>
#include <core_api/lsscaniterator.h>
#include <core_api/lssphericaliterator.h>

namespace SCENE_API {

// Forward declarations
class LSScan_Implementation;

/**
 * Interface to access information and functionality of scans.
 * \version	SCENE API version 2.0.0.
 */
class LSScan : public LSObject
{
	LS_UNCOPYABLE(LSScan)

public:

	/// The different export formats that are supported.
	/// \version SCENE API version 2.0.10
	enum ExportFormat
	{
		DXF = 0,	///< Drawing Interchange Format (.dxf)
		E57 = 1,	///< ASTM E57 3D File Format (.e57)
		FLS = 2,	///< FARO Laser Scan Format (.fls)
		IGS = 3,	///< Initial Graphics Exchange Specification Format (.iges)
		POD = 4,	///< Pointools POD File Format (.pod)
		PTS = 5,	///< Leica PTS File Format (.pts)
		PTX = 6,	///< Leica PTX File Format (.ptx)
		WRL = 7,	///< Virtual Reality Modeling Language File Format (.vrml)
		XYB = 8,	///< Binary XYZ File Format (.xyb)
		XYZ = 9,	///< ASCII XYZ File Format (.xyz)
		CPE = 10,	///< CPE File Format (.cpe)
		BMP = 11,	///< Bitmap Image File Format (.bmp)
		JPG = 12,	///< JPEG Image File Format (.jpg)
		PNG = 13,	///< PNG Image File Format (.png)
		TIF = 14,	///< TIFF Image File Format (.tif)
		LAS = 15	///< LAS File Format (.las, .laz)
	};

	/// The different data formats that are supported by FARO scans.
	/// \version	SCENE API Version 2.0.0.
	enum DataFormat
	{
		COLOR,		///< Color (RGB) information
		REFLECTION,	///< Reflection (Intensity) information
		AUTO,		///< Automatic selection of the color format
		COLOR_AND_REFLECTION	///< Color (RGB) and Reflection (Intensity) information at the same time
	};

	/// Determines whether data is available in the specified format.
	/// \param	format	The data format to check the availability for.
	/// \return	true if the data is available in the specified format, false
	/// otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool dataAvailable(DataFormat format = AUTO) const;

	/// Determines whether data is loaded in the specified format.
	/// \param	format	The data format to check the load state for.
	/// \return	true if the data is loaded in the specified format, false
	/// otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool dataLoaded(DataFormat format = AUTO) const;

	/// Load the scan data in the specified format.
	/// \param	format	The data format to load.
	/// \return	LSResult::Ok Loading was successful.
	///			LSResult::InvalidRequest The supplied parameters are wrong or the project needs to be saved first.
	///			LSResult::Unauthorized You do not have the API key required to load this scan.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSResult::Result loadData(DataFormat format = AUTO);

	/// Unloads the scan data.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void unloadData();

	/// Exports the scan data in the defined format.
	/// ATTENTION: Make sure that the data is available and loaded in 
	/// any format before calling this method! 
	/// \param	filePath	The path to the export destination.
	/// \param	format		The format to be used for the export. Supported formats are DXF, E57,
	///						FLS, IGS, POD, PTS, PTX, WRL, XYB, XYZ, CPE, LAS, BMP, JPG, PNG and TIF.
	/// \version			SCENE API Version 2.0.4.
	CORE_API_EXPORT LSResult::Result exportData(
		LSString filePath, 
		ExportFormat format);

	/// Gets a scan iterator which allows to iterate over the available scan
	/// data. The returned points are in global coordinates.
	/// ATTENTION: Make sure that the data is available and loaded in 
	/// any format before calling this method! If this iterator is used
	/// to iterate over reflection data, the intensity values will be
	/// mapped to RGB values using a contrast enhancement algorithm.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSScanIterator<LSPointXYZRGB> getScanIterator();

	/// Gets a scan iterator which allows to iterate over the available
	/// scan data. The returned points are in global coordinates.
	/// ATTENTION: Make sure that reflection data is available and
	/// loaded before calling this method!
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSScanIterator<LSPointXYZI> getScanReflectionIterator();

	/// \brief	Determines whether spatial scan data (scan point cloud) is available for this scan.
	/// \return	true if spatial data is available, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool spatialDataAvailable() const;

	/// Exports the spatial scan data in the defined format.
	/// \param	filePath	The path to the export destination.
	/// \param	format		The format to be used for the export. Supported formats are
	///						DXF, E57, IGS, POD, PTS, WRL, XYB, XYZ, CPE and LAS.
	/// \version			SCENE API Version 2.0.4.
	CORE_API_EXPORT LSResult::Result exportSpatialData(
		LSString filePath, 
		ExportFormat format);

	/// Gets an iterator which allows to iterate over the spatial scan data (scan point cloud).
	/// Call spatialDataAvailable() to check there is spatial data available for this scan.
	/// The returned points are in global coordinates.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSIterator<LSPointXYZRGB> getSpatialScanIterator();

	/// Gets an iterator which allows to iterate over the structured scan data (r, phi, theta).
	/// This iterator will return points in the scans local coordidate system. All non-existing
	/// or deleted points will return with zero distance (r=0). 
	/// ATTENTION: Call this method only on structured scans and loaded data! Make sure that the
	/// data is available and loaded in any format before calling this method! If this iterator is
	/// used to iterate over reflection data, the intensity values will be mapped to RGB values
	/// using a contrast enhancement algorithm.
	/// 
	/// Our polar coordinates are defined as follows:
	///
	/// x axis points equals to horizontal direction of 1. scan beam
	/// z axis is equal to the up direction
	/// phi is meant to be turned in clockwise direction
	/// theta == 0 in horizontal direction
	/// phi <-- [0,2*PI], theta <-- [0,PI[
	///
	/// (1) x =  radius * cos(phi) * cos(theta)
	/// (2) y = -radius * sin(phi) * cos(theta)
	/// (3) z =  radius * sin(theta)
	/// 
	/// 
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.31.
	CORE_API_EXPORT LSSphericalIterator<LSPointSphericalRGB> getSphericalCoordinatesIterator();

	/// Gets the scanner parameters which were used to take the scan.
	/// Will return a null pointer for non-FARO-scans, for example imported E57 files!
	/// \return	The attribute container containing the scanner parameters.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ref_ptr<const LSAttributeContainer> getScannerParameters();

	/// Gets the scanner parameters which were used to take the scan.
	/// Will return a null pointer for non-FARO-scans, for example imported E57 files!
	/// \return	The attribute container containing the scanner parameters.
	/// \version	SCENE API Version 2.0.22.
	CORE_API_EXPORT ref_ptr<const LSAttributeContainer> getScannerParameters() const;

	/// Gets the number of available columns.
	/// \return		The number of available columns.
	/// \version	SCENE API Version 2.0.5
	CORE_API_EXPORT int getNumCols() const;

	/// Gets the number of available rows.
	/// \return		The number of available rows.
	/// \version	SCENE API Version 2.0.5
	CORE_API_EXPORT int getNumRows() const;

	/// Sets the RGB color value of the point at the specified col/row position.
	/// Make sure that the scan is loaded with color data before calling this method!
	/// \param	col		The points column position.
	/// \param	row		The points row position.
	/// \param	r		The points red value will be set to this. Allowed range is [0,255].
	/// \param	g		The points green value will be set to this. Allowed range is [0,255].
	/// \param	b		The points blue value will be set to this. Allowed range is [0,255].
	/// \version		SCENE API Version 2.0.0.
	CORE_API_EXPORT void setPointColor(int col, int row, uint8_t r, uint8_t g, uint8_t b);

	/// Sets the reflection value of the point at the specified col/row position.
	/// Make sure that the scan is loaded with reflection data before calling this method!
	/// \param	col			The points column position.
	/// \param	row			The points row position.
	/// \param	reflection	The points reflection will be set to this value; range [0,1].
	/// \version			SCENE API Version 2.0.9.
	CORE_API_EXPORT void setPointReflection(int col, int row, float reflection);

	/// Deletes the point at the specified its col/row position.
	/// This will only mark the 3D and depth information for this point as deleted.
	/// The color and reflection values remain unchanged.
	/// Make sure that the scan data is loaded before calling this method!
	/// \version SCENE API Version 2.0.0.
	CORE_API_EXPORT void deletePoint(int col, int row);

	/// Creates a rectangular selection on the scan.
	/// \param	colLeft			The left points column position.
	/// \param	colRight		The right points column position.
	/// \param	rowTop			The top points row position.
	/// \param	rowBottom		The bottom points row position.
	/// \version				SCENE API Version 2.0.9.
	CORE_API_EXPORT void select2d(int colLeft, int colRight, int rowTop, int rowBottom);

	/// Get overlap areas of the scan. This method requires the scan to be loaded.
	/// FARO scans can contain areas with overlap where the scanner recorded more than 180 degrees for a scan half.
	/// Scans without overlap, for example imported unstructured scans, return 0 for all output parameters.
	/// \param	startColumn1	Output parameter with the starting column of the first overlap area.
	/// \param	columns1		Output parameter with size of the first overlap area in columns.
	/// \param	startColumn2	Output parameter with the starting column of the second overlap area.
	/// \param	columns2		Output parameter with size of the second overlap area in columns.
	/// \return					InvalidRequest if the scan was not loaded, Ok if the request was successful.
	/// \version				SCENE API Version 2.0.20.
	CORE_API_EXPORT LSResult::Result getOverlap(int& startColumn1, int& columns1, int& startColumn2, int& columns2) const;

	/// Check if a scan contains unstructured data. Structured data is organized in rows and columns.
	/// Unstructured scans are just a list of 3D points in no meaningful order.
	/// Do NOT use their row and column indices to determine the neighboring points!
	/// A typical example for structured data are Focus laser scans with proper rows and columns.
	/// A typical example for unstructured data are Freestyle scans or imported CPE files.
	/// \return		True, if the scan contains unstructured data.
	/// \version	SCENE API Version 2.0.21.
	CORE_API_EXPORT bool isUnstructured() const;

	/// Gets the RGB color value of the point at the specified col/row position.
	/// Make sure that the scan is loaded with color data before calling this method!
	/// \param		col		The points column position.
	/// \param		row		The points row position.
	/// \param		r		Red output parameter, will be set to a value in the range [0,255].
	/// \param		g		Green output parameter, will be set to a value in the range [0,255].
	/// \param		b		Blue output parameter, will be set to a value in the range [0,255].
	/// \return				True, if the color was extracted and copied to the output parameters.
	/// \version			SCENE API Version 2.0.22.
	CORE_API_EXPORT bool getPointColor(int col, int row, uint8_t& r, uint8_t& g, uint8_t& b) const;

	/// Overloaded method. Gets the RGB color value of the point at the specified col/row position.
	/// Make sure that the scan is loaded with color data before calling this method!
	/// \param		col		The points column position.
	/// \param		row		The points row position.
	/// \param		r		Red output parameter, will be set to a value in the range [0,255].
	/// \param		g		Green output parameter, will be set to a value in the range [0,255].
	/// \param		b		Blue output parameter, will be set to a value in the range [0,255].
	/// \param		isRGB	Flag that states wheather the color is a ScanPt RGB value. False, if the
	///						RGB value derived from encoded laser intensity/reflection values. 
	/// \return				True, if the color was extracted and copied to the output parameters. 
	/// \version			SCENE API Version 2.0.31.
	CORE_API_EXPORT bool getPointColor(int col, int row, uint8_t& r, uint8_t& g, uint8_t& b, bool& isRGB) const;

	/// Gets the reflection value of the point at the specified col/row position.
	/// Make sure that the scan is loaded with reflection data before calling this method!
	/// \param		col			The points column position.
	/// \param		row			The points row position.
	/// \param		reflection	This output parameter will be set to a value in the range [0,1].
	/// \return					True, if the reflection was extracted and copied to the output parameter.
	/// \version				SCENE API Version 2.0.22.
	CORE_API_EXPORT bool getPointReflection(int col, int row, float& reflection) const;

	/// Gets a scan iterator which allows to iterate over the available scan
	/// data. The returned points and normal vectors are in global coordinates.
	/// ATTENTION: Make sure that the data is available and loaded in
	/// any format before calling this method! Further, this method should
	/// be called on the processed data for getting accurate values of the
	/// components of the normal vector.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.25.
	CORE_API_EXPORT LSScanIterator<LSPointXYZN> getScanNormalsIterator();

	/// Gets the normal vector components of the point at the specified col/row position.
	/// Make sure that the scan is loaded with any data format before calling this method!
	/// Further, this method should be called on the scan which is processed for getting accurate
	/// values of the components of the normal vector 
	/// \param		col			The points column position. 
	/// \param		row			The points row position. 
	/// \param		nX			X component of the normal vector. 
	/// \param		nY			Y component of the normal vector.
	/// \param		nZ			Z component of the normal vector. 
	/// \return					True, if the components of the normal vector were extracted and copied to the output parameters. 
	/// \version				SCENE API Version 2.0.25.
	CORE_API_EXPORT bool getPointNormal(int col, int row, float& nX, float& nY, float& nZ) const;

	/// Gets a scan iterator which allows to iterate over the available spatial scan data (scan point cloud)
	/// and extract its corresponding normals. The returned points are in global coordinates.
	/// See also getSpatialScanIterator() and spatialDataAvailable().
	/// ATTENTION: Make sure that the spatial data is available before calling this method! 
	/// Further, this method should be called on the processed data for getting accurate values of the
	/// components of the normal vector.
	/// \return	The iterator instance.
	/// \version	SCENE API Version 2.0.26.
	CORE_API_EXPORT LSIterator<LSPointXYZN> getSpatialScanNormalsIterator();


	/// fills row/col with coordinates of nearest scan point to given atime. 
	/// returns true on success
	CORE_API_EXPORT LSResult::Result getNearestScanPoint(const uint64_t& time, int& row, int& col) const;

	/// fills automation time with time of given scan point
	CORE_API_EXPORT LSResult::Result getTimeOfScanPoint(int row, int col, uint64_t& time) const;

	/// fills the automation time with time of sync pulse which was issued before given column was scanned.
	/// the automation time of sync for column at (180 degree+x) is the same as at (x).
	CORE_API_EXPORT LSResult::Result getTimeOfSyncPulse(int col, uint64_t& time) const;

protected:
	LS_INTERFACE(LSScan, LSObject)
};

}
