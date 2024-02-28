#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsattributecontainer.h>
#include <core_api/lstask.h>
#include <core_api/lssignal.h>
#include <core_api/lsevent.h>

namespace SCENE_API {

// Forward declarations
class LSAppContext_Implementation;

/// Interface to general information and functionality of the application 
/// environment.
/// \version	SCENE API Version 2.0.0.
class LSAppContext : public LSAttributeContainer
{
	LS_UNCOPYABLE(LSAppContext)

public:

	/// Unit of measurement of length
	enum class LengthUnit : unsigned int
	{
		Meter = 0,		///< Meter (m), base metric unit for length
		Centimeter = 1, ///< Centimeter (cm), metric unit for length, 1/100 of a Meter (m)
		Millimeter = 2, ///< Millimeter (mm), metric unit for length, 1/10 of a Centimeter (cm)
		Yard = 3,		///< Yard (yd), imperial base unit of length
		Feet = 4,		///< Feet (ft), imperial unit of length, 1/3 of a Yard (yd)
		Inch = 5,		///< Inch (in), imperial unit of length, 1/12 of a Feet (yd)
		YardUS = 6,		///< YardUS, (yd US), US surveyor unit of length, 3 FeetUS (ft US)
		FeetUS = 7,		///< FeetUS, (ft US), US surveyor base unit of length
		InchUS = 8,		///< InchUS, (in US), US surveyor unit of length, 1/12 of a InchUS (yd US)
		LastItem
	};

	/// Unit of measurement of an angle
	enum class AngleUnit : unsigned int
	{
		Degree = 0, ///< Defined by full rotation of 360 degrees
		Radian = 1, ///< Arc of a circle with the same length as the radius of that circle subtends an angle of 1 radian
		Gon = 2,	///< Defined as one hundredth of the right angle
		LastItem
	};

	/// Gets the name of the calling app.
	/// \return	The name of the calling app.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString getAppName() const;

	/// Gets the version of the calling app.
	/// \return	The version of the calling app.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSString getAppVersion() const;

	/// Gets the API runtime version.
	/// This is either the API version of SCENE executing a plugin app or the
	/// API version of the standalone API runtime when running a standalone app.
	/// \see The header file lsapiversion.h contains a compile time API version number.
	/// \return	The API version as four dot-separated numbers in a string.
	/// \version	SCENE API Version 2.0.14.
	CORE_API_EXPORT LSString getApiVersion() const;

	/// Gets the tasks that are currently registered with this app context.
	/// \return	A map containing all registered tasks and their associated IDs.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSPod<std::map<LSString, ref_ptr<LSTask> > > getRegisteredTasks() const;

	/// Registers a task.
	/// \param	name	The name of the task to be registered. Each task of an
	/// app has to be unique within the scope of the app.
	/// \param	task	The task to be registered.
	/// \return	The ID of the task if it could be registered, if the task could
	/// not be registered an empty string is returned instead.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString registerTask(LSString name, ref_ptr<LSTask> task);
	
	/// \brief	Disables a task.
	/// \param	taskID	The ID of the task to be disabled.
	/// \return	true if the task could be disabled, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool disableTask(LSString taskID);

	/// Checks if the queried module is available in the host application (SCENE, ...).
	///
	/// Several module names exist start with SCENE API Version 2.0.16
	/// (introduction of this function), which are available for FARO internal
	/// usage only.
	///
	/// The following module names exist in `LSSceneContext`, starting with
	/// SCENE Plugin API Version 2.0.23:
	/// * `scene` -- is available in fully licensed SCENE instances.
	///              This includes trial licenses.
	/// * `scenenotrial` -- is available in fully licensed SCENE instances.
	///                     This does not include trial licenses.
	/// * `asbuiltmodeler` -- is available in fully licensed As-Built Modeler
	///                       instances. This includes trial licenses.
	/// * `asbuiltmodelernotrial` -- is available in fully licensed As-Built
	///                              Modeler instances. This does not include
	///                              trial licenses.
	///
	/// \param	moduleName	Name of the module to check.
	/// \return	True if available, false otherwise.
	/// \version	SCENE API Version 2.0.16 / 2.0.23
	CORE_API_EXPORT bool isModuleAvailable(LSString moduleName) const;

	/// Gets the units for length used in export.
	/// \return	The UnitsExportLength unit.
	/// \version	SCENE API Version 2.0.22.
	CORE_API_EXPORT LengthUnit getUnitsExportLength() const;

	/// Gets the units for length used in display setting.
	/// \return	The UnitsDisplayLength unit.
	/// \version	SCENE API Version 2.0.22.
	CORE_API_EXPORT LengthUnit getUnitsDisplayLength() const;

	/// Gets the units for angle used in display setting.
	/// \return	The UnitsDisplayAngle unit.
	/// \version	SCENE API Version 2.0.22.
	CORE_API_EXPORT AngleUnit getUnitsDisplayAngle() const;

	/// Gets the units for length used for small sizes display settings.
	/// \return	The UnitsDisplaySmallsizes unit.
	/// \version	SCENE API Version 2.0.22.
	CORE_API_EXPORT LengthUnit getUnitsDisplaySmallsizes() const;


	/// \name	Signals
	//@{

	/// \brief	Dispatched when the app context is being destroyed.
	/// \version	SCENE API Version 2.0.0.
	LSSignal<ref_ptr<LSEvent> > onClose;

	//@}

protected:
	LS_INTERFACE(LSAppContext, LSAttributeContainer)
};

}
