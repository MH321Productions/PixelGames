///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class StarterFrame
///////////////////////////////////////////////////////////////////////////////
class StarterFrame : public wxFrame
{
	private:

	protected:
		wxButton* btnStartTest;

		// Virtual event handlers, override them in your derived class
		virtual void onStartTest( wxCommandEvent& event ) { event.Skip(); }


	public:

		StarterFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PixelGames Starter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~StarterFrame();

};

