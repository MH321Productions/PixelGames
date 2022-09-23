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
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class StarterFrame
///////////////////////////////////////////////////////////////////////////////
class StarterFrame : public wxFrame
{
	private:

	protected:
		wxButton* btnStartTest;
		wxMenuBar* mainMenuBar;
		wxMenu* menuFile;
		wxMenu* menuHelp;

		// Virtual event handlers, override them in your derived class
		virtual void onStartTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPressQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void onLibraries( wxCommandEvent& event ) { event.Skip(); }


	public:

		StarterFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PixelGames Starter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~StarterFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog
{
	private:

	protected:
		wxTextCtrl* txtAbout;
		wxButton* btnGitHub;
		wxButton* btnClose;

		// Virtual event handlers, override them in your derived class
		virtual void onGithub( wxCommandEvent& event ) { event.Skip(); }
		virtual void onClose( wxCommandEvent& event ) { event.Skip(); }


	public:

		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About PixelGames"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,125 ), long style = wxDEFAULT_DIALOG_STYLE );

		~AboutDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LibrariesDialog
///////////////////////////////////////////////////////////////////////////////
class LibrariesDialog : public wxDialog
{
	private:

	protected:
		wxNotebook* nbLibs;
		wxButton* btnWebsite;
		wxButton* btnGithub;
		wxButton* btnClose;

		// Virtual event handlers, override them in your derived class
		virtual void onWebsite( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGithub( wxCommandEvent& event ) { event.Skip(); }
		virtual void onClose( wxCommandEvent& event ) { event.Skip(); }


	public:

		LibrariesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Libraries used by PixelGames"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,500 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LibrariesDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LibraryPanel
///////////////////////////////////////////////////////////////////////////////
class LibraryPanel : public wxPanel
{
	private:

	protected:
		wxStaticBitmap* imgLogo;
		wxStaticText* txtUsageDesc;
		wxStaticText* txtLicenseDesc;
		wxScrolledWindow* scrollUsage;
		wxTextCtrl* txtUsage;
		wxScrolledWindow* scrollLicense;
		wxTextCtrl* txtLicense;

	public:

		LibraryPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~LibraryPanel();

};

