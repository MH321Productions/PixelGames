#include "FormatterImpl.hpp"
#include "Resources.hpp"
#include "Util.hpp"
#include <sstream>
#include <fstream>
#include <wx/wx.h>
#include <iomanip>

using namespace std;

EntryDialogImpl::EntryDialogImpl(EntryPanelImpl* parent, const vector<Byte>& data)
: EntryBinDialog(parent), data(data), base64(Base64::encode(data)), frame(parent) {
    txtBase64->SetValue(base64);
}

void EntryDialogImpl::onSave(wxCommandEvent& event) {
    wxFileDialog dialog(this, "Save file", "", "", "Any file(*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() != wxID_OK) return;

    string path = dialog.GetPath().ToUTF8().data();

    //Write into file
    ofstream file(path, ios::binary);
    for (Byte& b: data) file << b;
    file.close();

    wxMessageBox("The resource was exported successfully", "Resource saved", wxOK | wxICON_INFORMATION, this);
}

void EntryDialogImpl::onLoad(wxCommandEvent& event) {
    wxFileDialog dialog(this, "Open file");
    if (dialog.ShowModal() != wxID_OK) return;

    string path = dialog.GetPath().ToUTF8().data();

    //Open file
    ifstream file(path, ios::binary);
    file.unsetf(ios::skipws);

    //Get size
    streampos size;
    file.seekg(0, ios::end);
    size = file.tellg();
    file.seekg(0, ios::beg);

    //Reserve capacity
    data.clear();
    data.reserve(size);

    //Read data
    data.insert(data.begin(), istream_iterator<Byte>(file), istream_iterator<Byte>());
    file.close();

    prepareValues();
    frame->setBinary(data);

    wxMessageBox("The resource was imported successfully", "Resource loaded", wxOK | wxICON_INFORMATION, this);
}

void EntryDialogImpl::onClose(wxCommandEvent& event) {
    Close();
}

void EntryDialogImpl::prepareValues() {
    base64 = Base64::encode(data);
    txtBase64->Clear();
    txtBase64->SetValue(base64);
}