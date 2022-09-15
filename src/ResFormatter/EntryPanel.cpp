#include "FormatterImpl.hpp"
#include "Resources.hpp"

using namespace std;

EntryPanelImpl::EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame)
: ResEntryPanel(parent), index(index), frame(frame), validator(wxFILTER_NONE) {}

EntryPanelImpl::EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame, const Resource& r)
: ResEntryPanel(parent), index(index), frame(frame), validator(wxFILTER_NONE) {
    txtName->SetValue(wxString::FromUTF8(r.name));
    
    if (r.isValid()) {
        choiceType->SetSelection(r.type);
        
        if (r.isBinary()) {
            btnValue->Enable();
            binValue = r.bin;
        } else {
            wxString val;
            if (r.isNumber()) val << r.number;
            else val = wxString::FromUTF8(r.text);

            txtValue->Enable();
            txtValue->SetValue(val);
        }
    }
}

void EntryPanelImpl::onType(wxCommandEvent& event) {
    ResourceType type = ResourceType(choiceType->GetSelection());

    if (type == Binary) {
        btnValue->Enable();
        txtValue->Disable();
    } else {
        btnValue->Disable();
        txtValue->Enable();

        if (type == Number) validator.SetStyle(wxFILTER_NUMERIC);
        else validator.SetStyle(wxFILTER_NONE);
        txtValue->SetValidator(validator);
    }
}

void EntryPanelImpl::onBinary(wxCommandEvent& event) {

}

void EntryPanelImpl::onDelete(wxCommandEvent& event) {
    frame->removeEntry(index);
}

Resource EntryPanelImpl::getResource() {
    return {};
}