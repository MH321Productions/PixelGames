#include "FormatterImpl.hpp"
#include "Util.hpp"
#include "Resources.hpp"
#include <wx/wx.h>
#include <map>

using namespace std;

class FormatterApp : public wxApp {
    public:
        virtual bool OnInit() {
            Windows::setupWindows();

            FormatterFrameImpl* frame = new FormatterFrameImpl;
            frame->Show();

            return true;
        }
};

wxIMPLEMENT_APP(FormatterApp);

void FormatterFrameImpl::onLoad(wxCommandEvent& event) {

}

void FormatterFrameImpl::onSave(wxCommandEvent& event) {
    wxFileDialog dialog(this, "Save resource", "", "", "Resource Files(*.res)|*.res", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() != wxID_OK) return;
    string filePath = string(dialog.GetPath().ToUTF8().data());
    if (!filePath.ends_with(".res")) filePath.append(".res");

    //Collect Resources
    map<string, Resource> res;

    Resource r;
    string name;
    for (EntryPanelImpl* entry: entries) {
        r = entry->getResource();
        if (r.isValid()) {
            name = r.getName();
            if (res.contains(name)) res.at(name) = r;
            else res.insert({name, r});
        }
    }

    //Save resources
    ResourceHandler handler("");
    handler.resources = res;
    if (handler.saveFile(filePath)) {
        wxMessageBox(wxT("The resources have been saved successfully"), wxT("Save Resources"), wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox(wxT("The resources couldn't be saved"), wxT("Save Resources"), wxOK | wxICON_ERROR, this);
    }
}

void FormatterFrameImpl::onAdd(wxCommandEvent& event) {
    addEntry({}); //Add empty entry
}

void FormatterFrameImpl::addEntry(const Resource& r) {
    size_t newIndex = entries.size();
    EntryPanelImpl* entry = new EntryPanelImpl(scroll, newIndex, this, r);
    resSz->Add(entry, 0, wxALL | wxEXPAND, 5);
    resSz->FitInside(scroll);
    entries.push_back(entry);
}

void FormatterFrameImpl::removeEntry(const size_t& index) {
    EntryPanelImpl* panel = entries.at(index);

    resSz->Remove(index);
    resSz->FitInside(scroll);
    entries.erase(entries.begin() + index);
    for (size_t i = index; i < entries.size(); i++) entries.at(i)->index = i;

    panel->Destroy();
}