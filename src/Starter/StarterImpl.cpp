#include "StarterImpl.hpp"
#include "Util.hpp"
#include <wx/wx.h>
#include <wx/stdpaths.h>

using namespace std;

class StarterApp : public wxApp {
    public:
        virtual bool OnInit() {
            Windows::setupWindows();
            wxImage::AddHandler(new wxPNGHandler);

            wxFileName f(wxStandardPaths::Get().GetExecutablePath());
            f.RemoveLastDir(); //To get main directory
            StarterFrameImpl* frame = new StarterFrameImpl(f.GetPath().ToUTF8().data());
            frame->Show(true);
            return true;
        }
};

wxDEFINE_EVENT(START_GAME, wxCommandEvent);
wxIMPLEMENT_APP(StarterApp);

StarterFrameImpl::StarterFrameImpl(const string& mainPath)
: StarterFrame(NULL), mainPath(mainPath), ipc(mainPath), currentGame(PongSingle) {
    wxLogInfo(wxString::FromUTF8(mainPath));

    Bind(START_GAME, &StarterFrameImpl::onGame, this);
}

void StarterFrameImpl::onStartTest(wxCommandEvent& event) {
    Hide();

    wxCommandEvent* ev = new wxCommandEvent(START_GAME);
    ev->SetInt(PongSingle);
    wxQueueEvent(this, ev);
}

void StarterFrameImpl::onGame(wxCommandEvent& event) {
    ipc.runGame(Games(event.GetInt()), this);
}

void StarterFrameImpl::onSettings(wxCommandEvent& event) {
    SettingsDialogImpl dialog(this);
    dialog.ShowModal();
}

void StarterFrameImpl::onPressQuit(wxCommandEvent& event) {
    Close();
}

void StarterFrameImpl::onAbout(wxCommandEvent& event) {
    AboutDialogImpl dialog(this);
    dialog.ShowModal();
}

void StarterFrameImpl::onLibraries(wxCommandEvent& event) {
    LibrariesDialogImpl dialog(this, mainPath);
    dialog.ShowModal();
}