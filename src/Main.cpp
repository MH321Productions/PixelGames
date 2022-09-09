#include <string>
#include <filesystem>

//System-based includes
#ifdef PG_WINDOWS
#include "WinInclude.hpp"
#else
#include <iostream>
#include <unistd.h>
#endif

using namespace std;
using namespace filesystem;

#ifndef PG_WINDOWS //POSIX Starter code

int main(int anzahl, char* args[]) {
    string exe = args[0];
    path cwd = current_path();

    //Get path for starter
    path starter;
    if (exe.at(0) == '/') { //Absolute path
        starter = path(exe).parent_path().append("bin").append("Starter");
    } else { //Relative path
        if (exe.starts_with("./")) { //current directory
            starter = cwd.append("bin").append("Starter");
        } else if (exe.starts_with("../")) { //super directory/directories
            starter = cwd.parent_path();
            exe = exe.substr(3);

            while (exe.starts_with("../")) {
                starter = starter.parent_path();
                exe = exe.substr(3);
            }

            starter.append("bin").append("Starter");

        } else { //subdirectories
            starter = cwd.append(exe).parent_path().append("bin").append("Starter");
        }
    }

    if (!exists(starter)) {
        cerr << "The starter " << starter.string() << " doesn't exist" << endl;
        return 1;
    }

    //Create new argument table
    char** newArgs = new char*[anzahl + 1];
    newArgs[0] = (char*) starter.c_str();
    for (int i = 1; i < anzahl; i++) newArgs[i] = args[i];
    newArgs[anzahl] = NULL;

    return execv(starter.c_str(), newArgs);
}

#else //WINAPI Starter code

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char exe[MAX_PATH];
    GetModuleFileName(NULL, exe, MAX_PATH); //Props to WINAPI for this neat function

    path starter = path(exe).parent_path().append("bin").append("Starter.exe");

    if (!exists(starter)) {
        string err = "The starter " + starter.string() + " doesn't exist!";
        MessageBox(NULL, err.c_str(), "Error while starting", MB_ICONERROR | MB_OK);
        return 1;
    }

    //Start Starter.exe
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(si);

    if (!CreateProcess(
        starter.string().c_str(),
        cmdline,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si, &pi
    )) {
        MessageBox(NULL, "Couldn't start the starter.\nPlease start bin\\Starter.exe manually", "Error while starting", MB_ICONERROR | MB_OK);
        return 1;
    }

    return 0;
}

#endif