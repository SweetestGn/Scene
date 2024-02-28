
#include <windows.h>

#include <core_api/lsproject.h>
#include <core_api/lslocalworkspace.h>
#include <standalone_api/lsstandalonecontext.h>

#include <iostream>
#include <fstream>

using namespace SCENE_API;

static void checkTime(ref_ptr<LSScan>);

/// @brief	Helper function which displays a file open dialog to select a 
///			project or local workspace.
static LSString selectProjectOrWorkspace()
{
	wchar_t fileName[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrTitle = L"Select a SCENE project or local workspace";
	ofn.lpstrFilter = L"SCENE Files (*.lsproj, *.fws)\0*.lsproj;*.fws\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (FALSE == GetOpenFileName(&ofn))
		return L"";
	else
		return fileName;
}

/// @brief	Application entry point
int wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow){
	// Standalone Apps always need to make sure to instantiate a standalone
	// context before using any other API functionality. This context has to
	// exist at least as along as any other API object!
	SCENE_API::LSStandaloneContext context;

	// Open a file selection dialog and let the user select a project or
	// workspace file
	LSString filePath = selectProjectOrWorkspace();
	if (filePath.empty())
		return 0;

	// Load the selected project or workspace
	if (filePath.rfind(L".lsproj") == filePath.length() - 7)
	{
		// The selected file is a project file -> Load the project
		ref_ptr<LSProject> project;
		LSResult::Result res = LSProject::loadProject(filePath, project, true /* readOnly */);
		if (res != LSResult::Ok)
		{
			MessageBox(NULL, L"The selected project could not be loaded!", L"Error", MB_OK | MB_ICONERROR);
			return 1;
		}
		res = context.setCurrentWorkspace(project);
		if (res != LSResult::Ok)
		{
			MessageBox(NULL, L"The selected project could not be set as current project!", L"Error", MB_OK | MB_ICONERROR);
			return 1;
		}

		// Acquire the number of scans contained in the workspace and display
		// the result to the user
		std::vector<ref_ptr<LSScan>> scans = project->getScans().get();
		std::wstringstream msg;
		msg << L"Project successfully loaded! The project contains " << scans.size() << L" scans.";
		MessageBox(NULL, msg.str().c_str(), L"Success", MB_OK | MB_ICONINFORMATION);
		//::checkTime(scans[0]);
		std::string dirFile = std::string("./data/output/");
		int counterScan = 1;
		for (ref_ptr<LSScan>& scan: scans)
		{
			scan->loadData();
			if (scan->dataLoaded()) {
				uint64_t timeOfScanPoint = 0;
				uint64_t t1 = 0;
				uint64_t timeCol = 0;
				std::wstringstream msgTime;
				std::wstringstream sizeStream;
				int rows = scan->getNumRows();
				int cols = scan->getNumCols();
				
				// We save the time of each station in rows and columns to the hard drive
				std::ofstream outFile(dirFile + std::to_string(counterScan) + ".csv");
				for (int row = 0; row < rows; ++row){
					for (int col = 0; col < cols; ++col) {
						scan->getTimeOfScanPoint(row, col, timeOfScanPoint);
						outFile << timeOfScanPoint << ",";
					}
					outFile << "\n";
				}
				outFile.close();
				counterScan++;
			}
			else
			{
				msg << L"I'm not OK ";
				MessageBox(NULL, msg.str().c_str(), L"Error", MB_OK | MB_ICONINFORMATION);
			}
		}
	}
	else
	{
		// The selected file is a local workspace file -> Load the workspace
		ref_ptr<LSLocalWorkspace> workspace;
		LSResult::Result res = LSLocalWorkspace::loadWorkspace(filePath, workspace);
		if (res != LSResult::Ok)
		{
			MessageBox(NULL, L"The selected workspace could not be loaded!", L"Error", MB_OK | MB_ICONERROR);
			return 1;
		}
		res = context.setCurrentWorkspace(workspace);
		if (res != LSResult::Ok)
		{
			MessageBox(NULL, L"The selected workspace could not be set as current workspace!", L"Error", MB_OK | MB_ICONERROR);
			return 1;
		}

		// Acquire the number of scans contained in the workspace and display
		// the result to the user
		std::vector<ref_ptr<LSScan> > scans = workspace->getScans().get();
		std::wstringstream msg;
		msg << L"Workspace successfully loaded! The workspace contains " << scans.size() << L" scans.";
		MessageBox(NULL, msg.str().c_str(), L"Success", MB_OK | MB_ICONINFORMATION);
	}

	return 0;
}

static void checkTime(ref_ptr<LSScan> scan) {

	scan->loadData();

	int rows = scan->getNumRows();
	uint64_t time = 0;
	//CPPUNIT_ASSERT(rows > 1);

	int cols = scan->getNumCols();

	/*CPPUNIT_ASSERT(cols > 1);

	CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfSyncPulse(1, time));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfScanPoint(1, 1, time));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getNearestScanPoint(time, row, col));*/



	// go col to col and check whether time of sync pulse is larger than preceding col

	const int startSecondHalf = (cols / 2);

	for (int col = 0; col < cols / 2; col++){

		uint64_t time1 = 0;

		uint64_t time2 = 0;

		scan->getTimeOfSyncPulse(col, time1);
		/*CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfSyncPulse(col, time1));

		CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfSyncPulse(col + 1, time2));*/
		scan->getTimeOfSyncPulse(col + 1, time2);
		if (!(time1 < time2)){
			MessageBox(NULL, L"col: time1 < time2!", L"Error", MB_OK | MB_ICONERROR);
		}
		//CPPUNIT_ASSERT(time1 < time2);

		// check that col from second half has same sync pulse

		uint64_t time1_2 = 0;
		scan->getTimeOfSyncPulse(col + startSecondHalf, time1_2);
		//CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfSyncPulse(col + startSecondHalf, time1_2));

		//CPPUNIT_ASSERT(time1 == time1_2);
		/*if (!(time1 == time2)) {
			MessageBox(NULL, L"time1 == time2!", L"Error", MB_OK | MB_ICONERROR);
		}*/

	}

	// go row to row and check whether time of scan point is smaller than preceding row in first half

	for (int row = 0; row < rows; row++){
		int col = startSecondHalf / 2;

		uint64_t time1 = 0;

		uint64_t time2 = 0;
		scan->getTimeOfScanPoint(row, col, time1);
		//CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfScanPoint(col, row, time1));
		scan->getTimeOfScanPoint(row + 1, col, time2);
		//CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfScanPoint(col, row + 1, time2));

		//CPPUNIT_ASSERT(time1 > time2);
		if (!(time1 > time2)) {
			MessageBox(NULL, L"row: time1 > time2!", L"Error", MB_OK | MB_ICONERROR);
		}
	}

	//... and larger in second half

	for (int row = 0; row < rows; row++){
		int col = startSecondHalf / 2 + startSecondHalf;

		uint64_t time1 = 0;

		uint64_t time2 = 0;
		scan->getTimeOfScanPoint(row, col, time1);
		scan->getTimeOfScanPoint(row + 1, col, time2);
		/*CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfScanPoint(col, row, time1));

		CPPUNIT_ASSERT_EQUAL_MESSAGE("should succeed as loaded", LSResult::Ok, scan->getTimeOfScanPoint(col, row + 1, time2));*/

		//CPPUNIT_ASSERT(time1 < time2);
		if (!(time1 < time2)) {
			MessageBox(NULL, L"row: time1 < time2!", L"Error", MB_OK | MB_ICONERROR);
		}
	}
}
