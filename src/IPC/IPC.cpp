#include <iostream>
#include <filesystem>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include "Util.hpp"
#include "IPC.hpp"

using namespace std;
using namespace filesystem;

const map<Games, string> IPC::paths {
    {PongSingle, "Pong-Single"}
};
const string IPC::pathPrefix = "bin";

#ifdef PG_WINDOWS
const string IPC::pathSuffix = ".exe";
#else
const string IPC::pathSuffix = "";
#endif

IPC::IPC(const std::string& programPath) {
    path program(programPath);
    program = program.parent_path();

    if (program.filename() == pathPrefix) mainPath = program.string();
    else {
        program.append(pathPrefix);
        if (exists(program)) mainPath = program.string();
        else {
            cerr << "Couldn't find minigame path";
            mainPath = current_path().string();
        }
    }

    cout << mainPath << endl;
}

string IPC::getPath(Games game) {
    return path(mainPath).append(paths.at(game) + pathSuffix).string();
}

bool IPC::checkAllGames() {
    for (unsigned char g = PongSingle; g <= PongSingle; g++) {
        if (!isGameAvailable(Games(g))) return false;
    }
    
    return true;
}

bool IPC::isGameAvailable(Games game) {
    return exists(getPath(game));
}

bool IPC::runGame(Games game, wxFrame* frame) {
    if (!isGameAvailable(game)) {
        wxString msg = wxT("Couldn't find the game:\n");
        msg << getPath(game) << " doesn't exist";

        wxMessageBox(msg, wxT("Couldn't start the game"), wxICON_ERROR, frame);
        return false;
    }
    frame->Show(false);

    GameReturn ret = runGameNative(getPath(game));

    if (ret.closeStarter) return true;

    frame->Show(true);

    if (ret.errors.size()) {
        wxString msg = wxT("The game had the following errors:\n");
        msg << ret.errors;
        wxMessageBox(msg, wxT("Errors while running the game"), wxICON_WARNING, frame);
    }

    return true;
}