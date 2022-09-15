#ifndef PG_FORMATTER_IMPL_HPP
#define PG_FORMATTER_IMPL_HPP

#include <vector>
#include "Formatter.h"
#include <wx/valtext.h>

using Byte = unsigned char;

class Resource;
class EntryPanelImpl;

class FormatterFrameImpl : public FormatterFrame {
    friend class EntryPanelImpl;
    private:
        std::vector<EntryPanelImpl*> entries;

        void addEntry(const Resource& r);
        void removeEntry(const size_t& index);

    protected:
        virtual void onLoad(wxCommandEvent& event);
        virtual void onSave(wxCommandEvent& event);
        virtual void onAdd(wxCommandEvent& event);

    public:
        FormatterFrameImpl() : FormatterFrame(NULL) {}
};

class EntryPanelImpl : public ResEntryPanel {
    friend class FormatterFrameImpl;
    protected:
        size_t index;
        std::vector<Byte> binValue;
        FormatterFrameImpl* frame;
        wxTextValidator validator;

        virtual void onType(wxCommandEvent& event);
        virtual void onBinary(wxCommandEvent& event);
        virtual void onDelete(wxCommandEvent& event);

    public:
        EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame, const Resource& r);
        EntryPanelImpl(wxWindow* parent, const size_t& index, FormatterFrameImpl* frame);

        Resource getResource();
};

#endif //PG_FORMATTER_IMPL_HPP