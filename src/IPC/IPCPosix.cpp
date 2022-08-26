/**
 * This file starts child processes using the POSIX API.
 * This should work on all unix-based systems (e.g. GNU/Linux, MacOS)
 */ 

#ifndef PG_WINDOWS

#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include "Util.hpp"
#include "IPC.hpp"

using namespace std;

GameReturn IPC::runGameNative(const string& path) {
    //Create file descriptors for pipe
    int fd[2];
    if (pipe(fd) == -1) {
        string error = "Couldn't create pipe: ";
        error.append(strerror(errno));
        return {-1, error, false};
    }

    pid_t id = fork();
    if (id == -1) {
        string error = "Couldn't fork: ";
        error.append(strerror(errno));
        return {-1, error, false};
    } else if (id == 0) { //Child process
        //Set pipe output to stderr/cerr
        dup2(fd[1], 2);
        close(fd[0]);

        //Execute game
        execl(path.c_str(), path.c_str(), mainPath.c_str(), "Test", NULL);
    }

    //Parent process
    close(fd[1]);

    //Wait for the child process to end
    int status, retCode = 0;
    if (waitpid(id, &status, 0) == -1) {
        string error = "waitpid failed: ";
        error.append(strerror(errno));
        return {-1, error, false};
    }

    if (WIFEXITED(status)) retCode = WEXITSTATUS(status); //Get return code

    //Read from pipe into buffer and string
    string err = "";
    char buffer[128];
    int numRead;

    while ((numRead = read(fd[0], buffer, 128)) > 0) {
        err.append(buffer, numRead);
    }
    close(fd[0]);

    //Return gathered data
    bool closeStarter = retCode == 1; //0 = keep starter open, 1 = close starter and the whole process, any other = error, keep starter open
    return {retCode, err, closeStarter};
}

#endif //PG_WINDOWS