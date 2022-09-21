#include "FormatterImpl.hpp"
#include "Resources.hpp"
#include <sstream>

using namespace std;

const wxString EntryPanelImpl::binValueSelected = wxT("Binary value");

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
            txtValue->SetValue(binValueSelected);
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
        tempText = txtValue->GetValue();
        txtValue->SetValue(binValueSelected);
        txtValue->Disable();
    } else {
        btnValue->Disable();
        txtValue->Enable();

        if (!tempText.IsEmpty()) {
            txtValue->SetValue(tempText);
            tempText.Clear();
        }

        if (type == Number) validator.SetStyle(wxFILTER_NUMERIC);
        else validator.SetStyle(wxFILTER_NONE);
        txtValue->SetValidator(validator);

        //Check if input is invalid
        if (!txtValue->Validate()) {
            wxString wrong = txtValue->GetValue(), correct;
            
            for (wxUniCharRef c: wrong) {
                if ((char) c >= '0' && (char) c <= '9') correct.Append(c);
            }
            txtValue->SetValue(correct);
        }
    }

    frame->setChanges();
}

void EntryPanelImpl::onBinary(wxCommandEvent& event) {
    EntryDialogImpl dialog(this, binValue);
    dialog.ShowModal();
}

void EntryPanelImpl::onDelete(wxCommandEvent& event) {
    frame->removeEntry(index);
    frame->setChanges();
}

void EntryPanelImpl::onText(wxCommandEvent& event) {
    frame->setChanges();
}

void EntryPanelImpl::setBinary(const std::vector<Byte>& data) {
    binValue = data;
    frame->setChanges();
}

Resource EntryPanelImpl::getResource() {
    ResourceType type = ResourceType(choiceType->GetSelection());
    string name = txtName->GetValue().ToUTF8().data();
    string text = txtValue->GetValue().ToUTF8().data();

    if (type == Text && !text.empty()) {
        return {name, text};
    } else if (type == Number && !text.empty()) {
        istringstream str;
        long number;
        str.str(text);
        str >> number;
        return {name, number};
    } else if (type == Binary && !binValue.empty()) {
        return {name, binValue};
    } else { //In case of empty or invalid data, return invalid resource
        return {};
    }
}