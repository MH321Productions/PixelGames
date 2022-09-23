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

    if (program.filename() == pathPrefix) {
        binPath = program.string();
        mainPath = program.parent_path().string();
    } else {
        mainPath = program.string();
        program.append(pathPrefix);
        if (exists(program)) binPath = program.string();
        else {
            cerr << "Couldn't find minigame path";
            binPath = current_path().string();
        }
    }

    cout << mainPath << endl;
}

string IPC::getPath(Games game) {
    return path(binPath).append(paths.at(game) + pathSuffix).string();
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

        wxMessageBox(msg, wxT("Couldn't start the game"), wxICON_ERROR, NULL);
        frame->Show(true);
        frame->Raise();
        frame->SetFocus();
        return false;
    }

    GameReturn ret = runGameNative(getPath(game));

    if (ret.closeStarter) {
        frame->Destroy();
        exit(0);
    }

    frame->Show(true);
    frame->Raise();
    frame->SetFocus();

    if (ret.errors.size()) {
        wxString msg = wxT("The game had the following errors:\n");
        wxString err = wxString::FromUTF8(ret.errors);
        msg << err;
        wxMessageBox(msg, wxT("Errors while running the game"), wxICON_WARNING, frame);
    }

    return true;
}