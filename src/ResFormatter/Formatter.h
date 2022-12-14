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
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/dialog.h>

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
		wxButton* btnNew;
		wxScrolledWindow* scroll;
		wxBoxSizer* resSz;

		// Virtual event handlers, override them in your derived class
		virtual void onClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAdd( wxCommandEvent& event ) { event.Skip(); }


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
		wxStaticText* lblName;
		wxTextCtrl* txtName;
		wxStaticText* lblType;
		wxChoice* choiceType;
		wxStaticText* lblValue;
		wxTextCtrl* txtValue;
		wxButton* btnValue;
		wxButton* btnDelete;

		// Virtual event handlers, override them in your derived class
		virtual void onType( wxCommandEvent& event ) { event.Skip(); }
		virtual void onText( wxCommandEvent& event ) { event.Skip(); }
		virtual void onBinary( wxCommandEvent& event ) { event.Skip(); }
		virtual void onDelete( wxCommandEvent& event ) { event.Skip(); }


	public:

		ResEntryPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,50 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~ResEntryPanel();

};

///////////////////////////////////////////////////////////////////////////////
/// Class EntryBinDialog
///////////////////////////////////////////////////////////////////////////////
class EntryBinDialog : public wxDialog
{
	private:

	protected:
		wxScrolledWindow* scrBase64;
		wxTextCtrl* txtBase64;
		wxButton* btnSave;
		wxButton* btnLoad;
		wxButton* btnClose;

		// Virtual event handlers, override them in your derived class
		virtual void onSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void onLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void onClose( wxCommandEvent& event ) { event.Skip(); }


	public:

		EntryBinDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Binary Resource"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,350 ), long style = wxDEFAULT_DIALOG_STYLE );

		~EntryBinDialog();

};

