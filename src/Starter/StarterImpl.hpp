#ifndef PG_STARTER_IMPL_HPP
#define PG_STARTER_IMPL_HPP

#include <string>
#include "StarterFrame.h"
#include "Resources.hpp"
#include "IPC.hpp"

wxDECLARE_EVENT(START_GAME, wxCommandEvent);

class LibraryPanelImpl;

class StarterFrameImpl : public StarterFrame {
    private:
        std::string mainPath;
        IPC ipc;
        Games currentGame;

        virtual void onStartTest(wxCommandEvent& event);
        virtual void onGame(wxCommandEvent& event);
        virtual void onSettings(wxCommandEvent& event);
        virtual void onPressQuit(wxCommandEvent& event);
        virtual void onAbout(wxCommandEvent& event);
        virtual void onLibraries(wxCommandEvent& event);

    public:
        StarterFrameImpl(const std::string& mainPath);
};

class AboutDialogImpl : public AboutDialog {
    protected:
        static const wxString urlGithub;

        virtual void onGithub(wxCommandEvent& event);
        virtual void onClose(wxCommandEvent& event);

    public:
        AboutDialogImpl(StarterFrameImpl* parent) : AboutDialog(parent) {}
};

class LibrariesDialogImpl : public LibrariesDialog {
    protected:
        ResourceHandler handler;
        std::vector<LibraryPanelImpl*> libs;

        virtual void onWebsite(wxCommandEvent& event);
        virtual void onGithub(wxCommandEvent& event);
        virtual void onClose(wxCommandEvent& event);

    public:
        LibrariesDialogImpl(StarterFrameImpl* parent, const std::string& mainPath);
};

class LibraryPanelImpl : public LibraryPanel {
    protected:
        std::string libName;

    public:
        std::string website, github;

        LibraryPanelImpl(wxWindow* parent, const ResourceHandler& handler, const std::string& libName);
};

class SettingsDialogImpl : public SettingsDialog {
    protected:

    public:
        SettingsDialogImpl(StarterFrameImpl* parent) : SettingsDialog(parent) {}
};

#endif //PG_STARTER_IMPL_HPP