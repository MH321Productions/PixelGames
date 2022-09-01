#include "StarterImpl.hpp"
#include "Util.hpp"
#include <wx/wx.h>

using namespace std;

class StarterApp : public wxApp {
    public:
        virtual bool OnInit() {
            Windows::setupWindows();

            StarterFrameImpl* frame = new StarterFrameImpl();
            frame->Show(true);
            return true;
        }
};

wxIMPLEMENT_APP(StarterApp);

StarterFrameImpl::StarterFrameImpl() : StarterFrame(NULL) {
    
}