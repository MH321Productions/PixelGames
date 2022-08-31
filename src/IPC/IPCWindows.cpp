/**
 * This file starts child processes using the Windows API (WINAPI).
 * This should therefore only work on Windows
 */ 

#ifdef PG_WINDOWS

#include <sstream>
#include "WinInclude.hpp"
#include "IPC.hpp"

using namespace std;

GameReturn IPC::runGameNative(const string& path) {
    //Create Pipe
    HANDLE pIn, pOut;
    if (!CreatePipe(&pIn, &pOut, NULL, 0)) {
        ostringstream str;
        str << "Couldn't create Pipe: " << GetLastError() << endl;
        return {-1, str.str(), false};
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.hStdError = pOut;

    char* mPath = mainPath.data();

    //Create Child process
    if (!CreateProcessA(
        path.c_str(),
        mainPath.data(),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si, &pi
    )) {
        ostringstream str;
        str << "Couldn't create Process: " << GetLastError() << endl;
        return {-1, str.str(), false};
    }

    //Read from Pipe
    char buffer[256];
    string err;
    unsigned long numRead;
    while (ReadFile(pIn, buffer, 256, &numRead, NULL) && numRead) {
        err.append(buffer, numRead);
    }

    //Wait for child process to end
    WaitForSingleObject(pi.hProcess, INFINITE);

    //Get exit code
    unsigned long getExit;
    int exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &getExit)) {
        err.append("\nCouldn't get exit code: " + GetLastError());
        exitCode = -1;
    } else exitCode = getExit;

    return {exitCode, err, getExit == 1};
}

#endif //PG_WINDOWS