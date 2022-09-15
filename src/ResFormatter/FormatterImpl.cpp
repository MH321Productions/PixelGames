#include "FormatterImpl.hpp"
#include "Util.hpp"
#include "Resources.hpp"
#include <wx/wx.h>

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