#include "StarterImpl.hpp"
#include <wx/msgdlg.h>
#include <wx/utils.h>

using namespace std;

LibrariesDialogImpl::LibrariesDialogImpl(StarterFrameImpl* parent, const std::string& mainPath) : LibrariesDialog(parent), handler(mainPath) {
    //Load resource file
    if (!handler.loadFile("libraries")) {
        wxMessageBox(wxT("Couldn't load the library resources"), wxT("Resource loader"), wxOK | wxICON_ERROR, parent);
        //return;
    }

    //Add resource panels
    LibraryPanelImpl* impl;

    impl = new LibraryPanelImpl(nbLibs, handler, "sfml");
    nbLibs->AddPage(impl, wxT("SFML"), true);
    libs.push_back(impl);

    impl = new LibraryPanelImpl(nbLibs, handler, "wx");
    nbLibs->AddPage(impl, wxT("wxWidgets"), false);
    libs.push_back(impl);

    impl = new LibraryPanelImpl(nbLibs, handler, "zlib");
    nbLibs->AddPage(impl, wxT("zlib"), false);
    libs.push_back(impl);

    wxSize temp = nbLibs->GetPage(0)->GetSize();
    cout << temp.GetWidth() << "x" << temp.GetHeight() << endl;
}

void LibrariesDialogImpl::onWebsite(wxCommandEvent& event) {
    string url = libs.at(nbLibs->GetSelection())->website;
    wxLaunchDefaultBrowser(wxString::FromUTF8(url));
}

void LibrariesDialogImpl::onGithub(wxCommandEvent& event) {
    string url = libs.at(nbLibs->GetSelection())->github;
    wxLaunchDefaultBrowser(wxString::FromUTF8(url));
}

void LibrariesDialogImpl::onClose(wxCommandEvent& event) {
    Close();
}