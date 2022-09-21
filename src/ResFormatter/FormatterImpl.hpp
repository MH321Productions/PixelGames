#ifndef PG_FORMATTER_IMPL_HPP
#define PG_FORMATTER_IMPL_HPP

#include <vector>
#include "Formatter.h"
#include <wx/valtext.h>

using Byte = unsigned char;

class Resource;
class EntryPanelImpl;
class EntryDialogImpl;

class FormatterFrameImpl : public FormatterFrame {
    friend class EntryPanelImpl;
    private:
        std::vector<EntryPanelImpl*> entries;
        bool hasChanges = false;
        wxString titleNormal, titleChanges;

        void addEntry(const Resource& r);
        void removeEntry(const size_t& index);

    protected:
        virtual void onLoad(wxCommandEvent& event);
        virtual void onSave(wxCommandEvent& event);
        virtual void onAdd(wxCommandEvent& event);
        virtual void onClose(wxCloseEvent& event);

    public:
        FormatterFrameImpl();
        void setChanges(const bool& openChanges = true);
};

class EntryPanelImpl : public ResEntryPanel {
    friend class FormatterFrameImpl;
    friend class EntryDialogImpl;
    protected:
        static const wxString binValueSelected;

        size_t index;
        std::vector<Byte> binValue;
        wxString tempText;
        FormatterFrameImpl* frame;
        wxTextValidator validator;

        virtual void onType(wxCommandEvent& event);
        virtual void onBinary(wxCommandEvent& event);
        virtual void onDelete(wxCommandEvent& event);
        virtual void onText(wxCommandEvent& event);

        void setBinary(const std::vector<Byte>& data);

    public:
        EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame, const Resource& r);
        EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame);

        Resource getResource();
};

class EntryDialogImpl : public EntryBinDialog {
    private:
        std::vector<Byte> data;
        wxString base64;
        EntryPanelImpl* frame;

        virtual void onSave(wxCommandEvent& event);
        virtual void onLoad(wxCommandEvent& event);
        virtual void onClose(wxCommandEvent& event);

        void prepareValues();

    public:
        EntryDialogImpl(EntryPanelImpl* parent, const std::vector<Byte>& data);
};

#endif //PG_FORMATTER_IMPL_HPP