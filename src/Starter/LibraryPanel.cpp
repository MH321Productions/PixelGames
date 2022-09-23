#include "StarterImpl.hpp"
#include <wx/bitmap.h>
#include <wx/mstream.h>

using namespace std;

LibraryPanelImpl::LibraryPanelImpl(wxWindow* parent, const ResourceHandler& handler, const string& libName)
: LibraryPanel(parent), libName(libName) {

    github = handler.getResource(libName + ".github").getText();
    website = handler.getResource(libName + ".website").getText();
    txtUsage->SetValue(wxString::FromUTF8(handler.getResource(libName + ".usage").getBinaryAsString()));
    txtLicense->SetValue(wxString::FromUTF8(handler.getResource(libName + ".license").getBinaryAsString()));

    //Load image
    vector<Byte> logo = handler.getResource(libName + ".logo").getBinary();
    if (logo.empty()) return; //If there is no logo, skip it

    wxMemoryInputStream str(logo.data(), logo.size());
    wxImage img(str, wxBITMAP_TYPE_PNG);
    cout << boolalpha << img.IsOk() << endl;
    if (img.IsOk()) imgLogo->SetBitmap(wxBitmap(img));
}