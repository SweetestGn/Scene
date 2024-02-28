#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsstring.h>
#include <core_api/lsattributecontainer.h>

#include <scanner_api/lsfuturetask.h>

namespace SCENE_API {

// Forward declarations
class LSScanner_Implementation;

/// The general interface to connect and communicate with a FARO Focus laser scanner.
/// This interface only supports Focus scanner models up to the V8 generation (Focus M and S series).
/// The newer generations (V9+) are not supported by this interface!
/// If you need to automate V9+ scanners, please contact the FARO customer service and ask for the LSWebAPI.
/// \version SCENE API Version 2.0.0.
class LSScanner : public LSInterface
{
	LS_UNCOPYABLE(LSScanner)

public:
	
	/// \brief Constructs a new scanner interface.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSScanner();

	/// \brief Destroys the scanner interface.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT virtual ~LSScanner();

	/// \brief Attempts to connect the scanner interface to the given address.
	/// \param	address	The scanner address in the format IP:Port (e.g.
	/// 192.168.0.1:8765). Keep in mind that the port is not related to
	/// the port for the web user interface that can be changed in the
	/// scanner UI. The port is fixed and should be always 8765.
	///	\return	An LSResult code.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSResult::Result connect(LSString address);

	/// \brief Disconnects the scanner interface from any connected scanner.
	///	\return     An LSResult code. Returns LSResult::Ok if not connected at
	///             the end of the call.
	/// \version	SCENE API Version 2.0.6.
	SCANNER_API_EXPORT LSResult::Result disconnect();

	/// \brief Take a scan which is stored locally on the scanner itself.
	/// \return	A LSFutureTask object which can be used to query the completion
	/// state and result of the requested operation.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSFutureTask> takeScan();

	/// Take a scan which is streamed over the network. No SD card required.
	/// This can be used to store a scan on the PC that controls the scanner.
	/// The supplied file path must be writable for the process that calls this method.
	/// For example it could be a local path or even a path to a SMB network share.
	/// Examples would be L"C:\\folder\\scan.fls" or L"\\\\host\\folder\\scan.fls".
	/// Currently the future will not report useful progress information.
	/// This method will return an error if the filePath already exists!
	/// \param	filePath	The file system path to the file in which the scan will be stored.
	///						Do not forget to escape any backslashes!
	/// \return				A LSFutureTask object which can be used to query the completion
	///						state and result of the requested operation.
	/// \version			SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSFutureTask> takeRemoteScan(LSString filePath);

	/// \brief Stops a running scan
	SCANNER_API_EXPORT void stopScan();

	/// \brief Shutdown the connected scanner.
	/// \return	true if the scanner could be shut down, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool shutdown();

	/// \brief Gets the currently active scan profile.
	/// \return	The current scan profile or a nullptr if the profile could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getCurrentScanProfile() const;

	/// \brief Sets the currently active scan profile.
	/// \param	scanProfile	The scan profile to be set.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool setCurrentScanProfile(ref_ptr<LSAttributeContainer> scanProfile);

	/// \brief Gets the list of available scan profiles.
	/// \return	The list of available scan profiles.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSPod<std::vector<ref_ptr<LSAttributeContainer> > > getScanProfiles() const;

	/// \brief Selects a profile from the list of available scan profiles and sets it as the currently active scan profile.
	/// \param	profileID	The profile ID of the profile to be selected.
	///	\return	bool if the profile could be selected, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool selectScanProfile(LSString profileID);

	/// \brief Adds a new profile to the list of available scan profiles.
	/// \param	scanProfile	The profile to be added to the list of scan profiles.
	/// \return	true if the profile could be added, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool addScanProfile(ref_ptr<LSAttributeContainer> scanProfile);

	/// \brief Removes a profile from the list of available scan profiles.
	/// \param	profileID	The profile ID of the profile to be removed.
	/// \return	true if the profile could be removed, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool removeScanProfile(LSString profileID);

	/// \brief Gets the list of available scan projects.
	/// \return	The list of available scan projects.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSPod<std::vector<ref_ptr<LSAttributeContainer> > > getScanProjects() const;

	/// \brief Selects a project from the list of available scan projects and sets it as the currently active scan project.
	/// \param	projectID	The project ID of the project to be selected.
	///	\return	bool if the project could be selected, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool selectScanProject(LSString projectID);

	/// \brief Adds a new project to the list of available scan projects.
	/// \param	scanProject	The project to be added to the list of scan projects.
	/// \return	true if the project could be added, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool addScanProject(ref_ptr<LSAttributeContainer> scanProject);

	/// \brief Removes a project from the list of available scan projects.
	/// \param	projectID	The project ID of the project to be removed.
	/// \return	true if the project could be removed, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool removeScanProject(LSString projectID);

	/// \brief Gets the list of available operators.
	/// \return	The list of available operators.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSPod<std::vector<ref_ptr<LSAttributeContainer> > > getOperators() const;

	/// Selects an operator from the list of available operators
	/// and sets it as the currently active operator.
	/// \param	operatorID	The operator ID of the operator to be selected.
	///	\return	bool if the operator could be selected, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool selectOperator(LSString operatorID);

	/// \brief Adds a new operator to the list of available operators.
	/// \param	scanOperator	The operator to be added to the list of operators.
	/// \return	true if the operator could be added, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool addOperator(ref_ptr<LSAttributeContainer> scanOperator);

	/// \brief Removes an operator from the list of available operators.
	/// \param	operatorID	The operator ID of the operator to be removed.
	/// \return	true if the operator could be removed, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool removeOperator(LSString operatorID);

	/// \brief Gets the general settings data container from the scanner.
	/// \return	The general settings data container or a nullptr if the settings could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getGeneralSettings() const;

	/// \brief Sets the general settings for the scanner.
	/// \param	settings	The general settings to be set.
	/// \return	true if the settings could be set, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool setGeneralSettings(ref_ptr<LSAttributeContainer> settings);

	/// \brief Gets a list of the scans which are stored on the scanner.
	/// \return	The list of scans which are stored on the scanner.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSPod<std::vector<ref_ptr<LSAttributeContainer> > > getScans() const;

	/// \brief Gets the properties of a scan which is stored on the scanner.
	/// \param	scanFile	The name of the scan for which the properties 
	/// should be retrieved.
	/// \return	The properties of the scan or a nullptr if the scan properties could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getScanProperties(LSString scanFile) const;

	/// \brief Gets the service information data container from the scanner.
	/// \return	The service information data container or a nullptr if the service information could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getServiceInformation() const;

	/// \brief Gets the sensor information data container from the scanner.
	/// \return	The sensor information data container or a nullptr if the sensor information could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getSensorInformation() const;

	/// \brief Gets the system version data container from the scanner.
	/// \return	The system version data container or a nullptr if the system version could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getSystemVersion() const;

	/// \brief Gets the firmware version data container from the scanner.
	/// \return	The firmware version data container or a nullptr if the firmware version could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getFirmwareVersion() const;

	/// \brief Gets the scanner status data container from the scanner.
	/// \note This method cannot be used to check if the scanner is still connected.
	/// It will typically just report an outdated status after the connection to the scanner
	/// was interrupted.
	/// \return	The scanner status data container or a nullptr if the status could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getScannerStatus() const;

	/// \brief Gets a list of the stored status messages from the scanner.
	/// \note Status messages are generated by the ID and the corresponding level, subject, text and
	/// solution proposition. The level defines the warning level: 1 = error, 3 = warning , 5 = info
	/// and 10 = no message. Status messages are removed from the block as soon they are no longer valid.
	/// \return	The list of stored status messages.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT LSPod<std::vector<ref_ptr<LSAttributeContainer> > > getStatusMessages() const;

	/// \brief Gets the current warning message from the scanner.
	/// \note Warnings are generated by the ID and the corresponding level, subject, text and solution proposition.
	/// The level defines the warning level: 1 = error, 3 = warning , 5 = info and 10 = no message. In most cases 
	/// it will require to manually resolve the problem on the scanner before to continue any operation.
	/// \return	The current warning message or a nullptr if the warning message could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getWarningMessage() const;

	/// \brief Gets the current set of scanner parameters from the scanner.
	/// \return	The current set of scanner parameters or a nullptr if the parameters could not be
	/// acquired (e.g. before the scanner was connected).
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT ref_ptr<LSAttributeContainer> getScannerParameters() const;

	/// \brief Sets the current set of scanner parameters for the scanner.
	/// \param	parameters	The parameters to be set for the scanner.
	/// \return	true if the parameters could be set, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	SCANNER_API_EXPORT bool setScannerParameters(ref_ptr<LSAttributeContainer> parameters);

	/// \brief Fetches a list of scanners available in the network.
	/// \note Works only for V6 and V7 scanner models. Not supported by the V8 scanners.
	/// \param	waitForMs	detectScanners sends a network broadcast message. waitForMS 
	///			defines the time to wait until all answers are collected and returned.
	/// \return	list of pairs of scanner serial number and its ip address. Empty list on error.
	/// \version	SCENE API Version 2.0.10.
	SCANNER_API_EXPORT LSPod<std::vector<std::pair<LSString, LSString>>> detectScanners(int waitForMs = 1000) const;

	/// \brief Gets the temperature of the sensor from inside the scanner.
	/// \param temperature Output for the current sensor temperature in degree Celsius.
	/// \return True if successful, false if the request failed due to connection loss or other problems.
	/// \version SCENE API Version 2.0.15.
	SCANNER_API_EXPORT bool getSensorTemperature(double& temperature) const;

protected:
	LS_INTERFACE(LSScanner, LSInterface)
};

}
