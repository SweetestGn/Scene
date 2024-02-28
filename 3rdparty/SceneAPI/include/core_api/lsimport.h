#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsreftype.h>
#include <core_api/lsresult.h>

namespace SCENE_API
{
	// Forward declarations
	class LSProject;
	class LSString;
	class LSScan;

	/// \defgroup import Import
	/// Functions and types related to the import functionality

	/// Interface for the import of unstructured point cloud data.
	/// You have to inherit and implement this interface to be able to call
	/// the function importPointData() successfully.
	/// \version SCENE API Version 2.0.21
	/// \ingroup import
	class LSPointDataSource : public LSRefType
	{
	public:
		virtual ~LSPointDataSource() {};

		/// Must return the next point each time it is called.
		/// This will be called once for every point in the data set.
		/// Each time this method is called, it should return the data of the next point.
		/// The order of the points is not important. If you provide structured data, the order 
		/// and position in the 2D grid is determined by the supplied row and column values.
		/// If you supply the same row/col combination twice, the first value will be overwritten!
		/// Return true if everything is okay, return false to signal an error and abort the import.
		/// In this case importPointData() will return asap with an InvalidRequest error.
		/// All parameters are output parameters!
		/// \param	position	Position of the scan point. Pointer to three values (X, Y, Z).
		/// \param	row			Row number, starting at zero. Pointer to one value.
		///						Will be ignored if isStructured() returned false.
		/// \param	column		Column number, starting at zero. Pointer to one value.
		///						Will be ignored if isStructured() returned false.
		/// \param	normal		Normal of the scan point. Pointer to three values (X, Y, Z).
		///						Will be ignored if hasNormals() returned false.
		/// \param	color		Color of the scan point. Pointer to three R, G, B bytes.
		///						Will be ignored if hasColors() returned false.
		/// \param	intensity	Intensity of the scan point. Pointer to one value.
		///						The valid range is between 0 and 1, so you may have to convert or
		///						scale your intensity/reflection/gray values.
		///						Will be ignored if hasIntensity() returned false.
		/// \version SCENE API Version 2.0.21
		virtual bool getNextPoint(
			double position[3],
			uint32_t& row,
			uint32_t& column,
			float normal[3],
			uint8_t color[3],
			float& intensity) = 0;

		/// Must return the exact overall number of points.
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual uint64_t getNumberOfPoints() const = 0;

		/// Must return true if the scan data is ordered in rows and columns.
		/// Structured points are sorted into a 2D grid based on the supplied row and column values.
		/// The number of overall points must be <= rows * columns.
		/// You do not need to set all points, if you do not set a position, it will stay empty.
		/// Return false if you just want to import a unstructured point cloud.
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual bool isStructured() const { return false; }

		/// Must return the exact number of rows.
		/// The returned value must be greater 0 for structured data.
		/// It will be only called if isStructured() returns true.
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual uint32_t getNumberOfRows() const { return 0; }

		/// Must return the exact number of cols.
		/// The returned value must be greater 0 for structured data.
		/// It will be only called if isStructured() returns true.
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual uint32_t getNumberOfCols() const { return 0; }

		/// Return true if all the points have valid normals.
		/// It no normals are supplied, SCENE might estimate them later.
		/// Since this process is far from perfect and can take a very long time for
		/// big point clouds, you should always supply normals if they are available.
		/// Only all or no points can have normals!
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual bool hasNormals() const { return false; }

		/// Return true if all the points are colored.
		/// Partially colored data sets are not supported.
		/// Keep in mind that only color OR intensity is supported!
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual bool hasColors() const { return false; }

		/// Return true if all the points have intensity values.
		/// Only all or no points can have an intensity value!
		/// Keep in mind that only color OR intensity is supported!
		/// This is only called once before the points are iterated!
		/// \version SCENE API Version 2.0.21
		virtual bool hasIntensity() const { return false; }
	};

	/// Import unstructured or structured point data directly from memory into the given project.
	/// This can be used to import point data without writing and reading files from disk.
	/// This can be used to write an importer for a proprietary point cloud file format.
	/// Currently only color or intensity is supported. This function cannot import both due to
	/// an internal limitation. Please keep in mind that the underlying implementation requires
	/// all points to fit in the computers memory. Very big data sets should therefore be
	/// separated into multiple chunks! The scan will be imported into the default scan folder
	/// (the "Scans" folder below the root object). Each successful call to this function will
	/// generate a new scan in the project tree. Here is a simple example: 
	///
	/// \code
	/// struct MyCylinderSource : public LSPointDataSource
	/// {
	/// 	const int points = 1000000;
	/// 	const double rotStep = 0.05;
	/// 	int currentPoint = 0;
	///
	/// 	uint64_t getNumberOfPoints() const override { return points; }
	/// 	bool hasColors() const override { return true; }
	///
	/// 	bool getNextPoint(
	///			double pos[3], uint32_t& row, uint32_t& col, float normal[3],
	///			uint8_t color[3], float& intensity) override
	/// 	{
	///			float factor = (float)currentPoint / points;
	/// 		pos[0] = sin(rotStep * currentPoint);
	/// 		pos[1] = cos(rotStep * currentPoint);
	/// 		pos[2] = factor * 3;
	/// 		color[0] = uint8_t(255 * factor);
	/// 		color[1] = 0;
	/// 		color[2] = uint8_t(255 * factor);
	///			return currentPoint++ < points;
	/// 	}
	/// };
	///
	/// ref_ptr<LSProject> project = ...;
	/// ref_ptr<LSPointDataSource> source = new MyCylinderSource();
	/// ref_ptr<LSScan> scan = nullptr;
	/// importPointData(project, L"my_magenta_cylinder", source, scan);
	/// \endcode
	///
	/// \param	project	The project that should receive the imported data as a new scan object.
	/// \param	name	The proposed name for the scan generated from the imported point data.
	///					If there is already something with that name, SCENE will generate a unique
	///					name by appending numbers. Retrieve the final name of the newly created scan
	///					by calling getName() on the objected returned through the scan parameter.
	/// \param	source	An instance of a implementation of the LSPointDataSource interface.
	/// \param	scan	Output parameter with a reference to the generated scan.
	///					Will stay empty if the import of the point data failed.
	/// \ingroup import
	/// \version SCENE API Version 2.0.21
	CORE_API_EXPORT LSResult::Result importPointData(
		const ref_ptr<LSProject>& project,
		const LSString& name,
		const ref_ptr<LSPointDataSource>& source,
		ref_ptr<LSScan>& scan);

} // namespace SCENE_API
