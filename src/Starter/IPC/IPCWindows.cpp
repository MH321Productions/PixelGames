/**
 * This file starts child processes using the Windows API (WINAPI).
 * This should therefore only work on Windows
 */ 

#ifdef PG_WINDOWS

#include "WinInclude.hpp"
#include <sstream>
#include "IPC.hpp"

using namespace std;

GameReturn IPC::runGameNative(const string& path) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    //Create Pipe
    HANDLE pIn, pOut;
    if (!CreatePipe(&pIn, &pOut, &sa, 0)) {
        ostringstream str;
        str << "Couldn't create Pipe: " << GetLastError() << endl;
        return {-1, str.str(), false};
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdError = pOut;
    si.cb = sizeof(si);

    char* mPath = mainPath.data();

    //Create Child process
    if (!CreateProcessA(
        path.c_str(),
        mainPath.data(),
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si, &pi
    )) {
        ostringstream str;
        str << "Couldn't create Process: " << GetLastError() << endl;
        return {-1, str.str(), false};
    }

    CloseHandle(pOut);

    //Wait for child process to end
    WaitForSingleObject(pi.hProcess, INFINITE);

    //Read from Pipe
    char buffer[256];
    string err;
    unsigned long numRead;
    while (ReadFile(pIn, buffer, 256, &numRead, NULL) && numRead) {
        if (!numRead) break;
        err.append(buffer, numRead);
    }

    //Get exit code
    unsigned long getExit;
    int exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &getExit)) {
        err.append("\nCouldn't get exit code: " + GetLastError());
        exitCode = -1;
    } else exitCode = getExit;

    CloseHandle(pIn);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return {exitCode, err, getExit == 1};
}

#endif //PG_WINDOWS