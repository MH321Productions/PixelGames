#ifndef PG_STARTER_IMPL_HPP
#define PG_STARTER_IMPL_HPP

#include <string>
#include "StarterFrame.h"
#include "IPC.hpp"

wxDECLARE_EVENT(START_GAME, wxCommandEvent);

class StarterFrameImpl : public StarterFrame {
    private:
        std::string programPath;
        IPC ipc;
        Games currentGame;

        virtual void onStartTest(wxCommandEvent& event);
        virtual void onGame(wxCommandEvent& event);

    public:
        StarterFrameImpl(const std::string& programPath);
};

#endif //PG_STARTER_IMPL_HPP