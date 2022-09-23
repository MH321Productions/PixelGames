#include "StarterImpl.hpp"
#include <wx/utils.h>

using namespace std;

const wxString AboutDialogImpl::urlGithub = wxT("https://github.com/MH321Productions/PixelGames");

void AboutDialogImpl::onGithub(wxCommandEvent& event) {
    wxLaunchDefaultBrowser(urlGithub);
}

void AboutDialogImpl::onClose(wxCommandEvent& event) {
    Close();
}