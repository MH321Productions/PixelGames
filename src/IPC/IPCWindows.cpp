/**
 * This file starts child processes using the Windows API (WINAPI).
 * This should therefore only work on Windows
 */ 

#ifdef PG_WINDOWS

#include <Windows.h>
#include "IPC.hpp"

using namespace std;

GameReturn IPC::runGameNative(const string& path) {
    //TODO: Implement process start with WINAPI
}

#endif //PG_WINDOWS