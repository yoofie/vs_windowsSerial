/* ********************************************************
	Name: vs_windowsSerial
	Author: @yoofie
	Website: http://yoofie.net
	Twitter: @y00fie
******************************************************** */

#include <iostream>
#include <vector>
#include <windows.h>
#include <tchar.h>
using namespace std;
/* ********************************************************
	Constants Defines
******************************************************** */
#define MAX_NUM_OF_BYTES 18
const uint8_t maxBytes = MAX_NUM_OF_BYTES + 1; // char max capacity. +1 bytes for terminating null character
const uint8_t VECTOR_MAX_CAPACITY = 128; // in bytes


/* ********************************************************
	Support Functions:
	==================
	printVec - use to printout the vector
	printBuffer - Print out plain char array
******************************************************** */
template<typename T>
void printVec(T& vec) {
	//cout << "Vector: ";
	for (auto& itr : vec) {
		cout << itr;
	}
	cout << "\n";
}



void printBuffer(char* const buff, uint8_t size) {
	for (size_t i = 0; i < size; i++) {
		cout << "" << buff[i];
	}
}


/* ********************************************************
	So it begins()
******************************************************** */
int main() {
	cout << "vs_WindowsSerial by @y00fie!\n";

#if defined(_WIN32) || defined(_WIN64)
#define SERIAL_PORT "COM11"
#endif
#if defined(__linux__) || defined(__APPLE__)
#define SERIAL_PORT "/dev/ttyACM0"
#endif

	// Open serial port
	HANDLE serialHandle;

	// Adjust Windows COM Port number here
	serialHandle = CreateFile(_T("\\\\.\\COM11"), GENERIC_READ | GENERIC_WRITE, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (serialHandle == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
		else {
			cout << "exists\n";
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	/* ********************************************************
		Serial Settings
	******************************************************** */
	dcbSerialParams.BaudRate = CBR_115200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serialHandle, &timeouts);
	if (!SetCommTimeouts(serialHandle, &timeouts)) {
		cout << "Error #1: Failed to set COMM timeout settings!\n";
	}

	if (!SetCommState(serialHandle, &dcbSerialParams)) {
		cout << "Error #2: Failed to set COMM timeout settings!\n";
	}

	/* ********************************************************
		Create some plain char buffers (for use plain ol' C)
		Also: Create char vectors (fior use with C++ STD lib)
	******************************************************** */
	char szBuff[maxBytes] = { 0 };
	char buff0[maxBytes + 1] = { 0 };
	char buff1[maxBytes + 1] = { 0 };
	char* ptr = buff0;
	cout << "Buff 0 Init\n";
	DWORD dwBytesRead = 0;

	/* ********************************************************
		Vectors
		Create vectors and pre-allocate VECTOR_MAX_CAPACITY bytes
	******************************************************** */
	vector<char> latestData;
	vector<char> prevData;

	latestData.reserve(VECTOR_MAX_CAPACITY);
	prevData.reserve(VECTOR_MAX_CAPACITY);

	/* ********************************************************
		Infinite Loop: Prints *new* serial data
		=======================================
		TO exit console, press CTRL + C to cancel application
	******************************************************** */
	while (1) {

		if (!ReadFile(serialHandle, ptr, maxBytes, &dwBytesRead, NULL)) {
			cout << "nok\n Bytes Read: " << dwBytesRead << "\n";
		}
		else {
			// This function compares old data with new data and saves the new data.
			// Paces new serial data to human readable speeds
			if (0 != memcmp(buff1, buff0, maxBytes)) {
				cout << "\nCycle:\n======\n";
				memcpy(buff1, buff0, maxBytes);

				// Prints raw char buffer
				//cout << "buff0: ";
				//printBuffer(ptr, n);

				// Prints C++ vector
				latestData.assign(buff0, buff0 + maxBytes);
				printVec(latestData);
				prevData = latestData;
				printVec(prevData);
			}
		}

		// You now have a buffer of serial data, do something with it
		
		// latestData vector for use with C++
		// buff0 char array for use with C
	}
}

