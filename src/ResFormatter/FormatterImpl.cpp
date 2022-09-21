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

FormatterFrameImpl::FormatterFrameImpl() : FormatterFrame(NULL) {
    titleNormal = GetTitle();
    titleChanges = wxT("*") + titleNormal;
}

void FormatterFrameImpl::onLoad(wxCommandEvent& event) {
    wxFileDialog dialog(this, "Open resource", "", "", "Resource Files (*.res)|*.res", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() != wxID_OK) return;
    string filePath = string(dialog.GetPath().ToUTF8().data());

    ResourceHandler handler("");
    if (!handler.loadIntern(filePath)) {
        wxMessageBox(wxT("The resources couldn't be loaded"), wxT("Load Resources"), wxOK | wxICON_ERROR, this);
        return;
    }

    for (const pair<string, Resource>& p: handler.resources) addEntry(p.second);

    wxMessageBox(wxT("The resources were loaded successfully"), wxT("Load Resources"), wxOK | wxICON_INFORMATION, this);
}

void FormatterFrameImpl::onSave(wxCommandEvent& event) {
    wxFileDialog dialog(this, "Save resource", "", "", "Resource Files (*.res)|*.res", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() != wxID_OK) {
        event.SetInt(1);
        return;
    }
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
        wxMessageBox(wxT("The resources were saved successfully"), wxT("Save Resources"), wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox(wxT("The resources couldn't be saved"), wxT("Save Resources"), wxOK | wxICON_ERROR, this);
    }

    event.SetInt(0);
    setChanges(false);
}

void FormatterFrameImpl::onAdd(wxCommandEvent& event) {
    addEntry({}); //Add empty entry
    setChanges();
}

void FormatterFrameImpl::onClose(wxCloseEvent& event) {
    //Can't cancel event
    if (!event.CanVeto() || !hasChanges) {
        Destroy();
        return;
    }

    int result = wxMessageBox(
        wxT("You have unsaved changes. Do you want to save before closing?"),
        wxT("Unsaved Changes"), wxYES_NO | wxCANCEL | wxICON_QUESTION, this
    );
    wxCommandEvent dummy;
    switch (result) {
        case wxCANCEL:
            event.Veto();
            break;
        case wxNO:
            Destroy();
            break;
        case wxYES:
            onSave(dummy);
            if (dummy.GetInt() == 1) event.Veto(); //Save dialog aborted, keep open
            else Destroy(); //Save dialog finished, close
            break;
        default:
            Destroy();
    }
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

void FormatterFrameImpl::setChanges(const bool& openChanges) {
    if (hasChanges == openChanges) return;
    hasChanges = openChanges;

    if (hasChanges) SetTitle(titleChanges);
    else SetTitle(titleNormal);
}