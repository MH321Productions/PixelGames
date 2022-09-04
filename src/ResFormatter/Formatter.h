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
#include <wx/scrolwin.h>
#include <wx/frame.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FormatterFrame
///////////////////////////////////////////////////////////////////////////////
class FormatterFrame : public wxFrame
{
	private:

	protected:
		wxButton* btnLoad;
		wxButton* btnSave;
		wxScrolledWindow* scroll;

		// Virtual event handlers, override them in your derived class
		virtual void onLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSave( wxCommandEvent& event ) { event.Skip(); }


	public:

		FormatterFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Resource Formatter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~FormatterFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ResEntryPanel
///////////////////////////////////////////////////////////////////////////////
class ResEntryPanel : public wxPanel
{
	private:

	protected:

	public:

		ResEntryPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,50 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~ResEntryPanel();

};

