#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsstring.h>
#include <core_api/lsattributecontainer.h>
#include <core_api/lssignal.h>
#include <core_api/lspointtypes.h>
#include <core_api/lsscan.h>
#include <core_api/lsproject.h>
#include <core_api/lserror.h>

#include <scanner_api/lssensorevent.h>

namespace SCENE_API {

// Forward declarations
class LSSensor_Implementation;

/// The general interface to connect and communicate with a FARO sensor devices.
/// \version SCENE API Version 2.0.14.
class LSSensor : public LSInterface, public LSRefType
{
	LS_UNCOPYABLE(LSSensor)

public:
	/// \version	SCENE API Version 2.0.14.
	SCANNER_API_EXPORT LSSensor();

	/// \version	SCENE API Version 2.0.14.
	SCANNER_API_EXPORT ~LSSensor();

	/// Connects to a sensor.
	/// \pre			An open workspace (see LSSceneContext::openSceneWorkspace()
	///					or LSStandaloneContext::setCurrentWorkspace())
	/// \param id		The id of the sensor to connect to.
	/// \param timeout	The timeout for the connection attempt.
	///	\return			An LSResult code.
	/// \version		SCENE API Version 2.0.14.
	SCANNER_API_EXPORT ref_ptr<LSError> connect(LSString id, float timeout = 30.f);

	/// Fetches a list of available sensors.
	/// \return		A list of detected sensors, each pair contains the serial number and the id.
	/// \version	SCENE API Version 2.0.14.
	SCANNER_API_EXPORT LSPod<std::vector<std::pair<LSString, LSString>>> detectSensors() const;

	/// Event that is triggered when a sensor device has been removed.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onSensorDisconnected();

	/// Event that is triggered when the user intends to start scanning.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanStartTriggered();

	/// Event that is triggered when scanning has started.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanStarted();

	/// Event that is triggered when tracking has been lost.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanTrackingLost();

	/// Event that is triggered when tracking has been found.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanTrackingFound();

	/// Event that is triggered when the user intends to stop scanning.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanStopTriggered();

	/// Event that is triggered when scanning has stopped and the scan is completed.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT SENSOR_SIGNAL(void)& onScanCompleted();

	/// Event that is triggered when new video data is available.
	/// \version SCENE API Version 2.0.14.
	typedef Eigen::Matrix<Eigen::Vector3uc, Eigen::Dynamic, Eigen::Dynamic> VideoData;
	SCANNER_API_EXPORT FRAME_SIGNAL(VideoData)& onVideoData();

	/// Event that is triggered when new point data is available.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT FRAME_SIGNAL(LSPod<std::vector<LSPointXYZRGB>>)& onPointData();

	/// Event that is triggered each time a frame's pose is updated.
	/// Use the pose to convert a frame's points to world coordinates.
	/// \version SCENE API Version 2.0.14.
	SCANNER_API_EXPORT FRAME_SIGNAL(Eigen::Matrix4d)& onUpdateFramePose();


	/// Hardware buttons.
	/// \version SCENE API Version 2.0.17.
	enum class Button {
		LEFT, ///< Left button.
		MIDDLE, ///< Middle button.
		RIGHT ///< Right button.
	};

	/// Events for hardware buttons.
	/// \version SCENE API Version 2.0.17.
	enum class ButtonEvent {
		CLICK, ///< Normal click (press and release).
		DOUBLECLICK, ///< Double click (two fast normal clicks).
		PRESS, ///< Button down.
		RELEASE ///< Button up.
	};

	/// Button info containing hardware button and event.
	/// \version SCENE API Version 2.0.17.
	struct ButtonInfo {
		Button button; ///< The button that caused the event.
		ButtonEvent event; ///< The button event type.
	};

	/// Event that is triggered when a hardware button event occurs
	/// \version SCENE API Version 2.0.17.
	SCANNER_API_EXPORT SENSOR_SIGNAL(ButtonInfo)& onButtonEvent();

	/// Starts the scanning process.
	/// \version SCENE API Version 2.0.17.
	SCANNER_API_EXPORT LSResult::Result start();

	/// Stops the scanning process.
	/// \version SCENE API Version 2.0.17.
	SCANNER_API_EXPORT LSResult::Result stop();

protected:
	LS_INTERFACE(LSSensor, LSInterface)
};

}