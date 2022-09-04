#include "FormatterImpl.hpp"
#include "Util.hpp"
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