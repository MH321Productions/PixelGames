#include "StarterImpl.hpp"
#include "Util.hpp"
#include <wx/wx.h>
#include <wx/stdpaths.h>

using namespace std;

class StarterApp : public wxApp {
    public:
        virtual bool OnInit() {
            Windows::setupWindows();

            wxFileName f(wxStandardPaths::Get().GetExecutablePath());
            StarterFrameImpl* frame = new StarterFrameImpl(f.GetPath().ToUTF8().data());
            frame->Show(true);
            return true;
        }
};

wxDEFINE_EVENT(START_GAME, wxCommandEvent);
wxIMPLEMENT_APP(StarterApp);

StarterFrameImpl::StarterFrameImpl(const string& programPath)
: StarterFrame(NULL), programPath(programPath), ipc(programPath), currentGame(PongSingle) {
    wxLogInfo(wxString::FromUTF8(programPath));

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