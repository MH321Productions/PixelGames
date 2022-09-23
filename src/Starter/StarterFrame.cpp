///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "StarterFrame.h"

///////////////////////////////////////////////////////////////////////////

StarterFrame::StarterFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	btnStartTest = new wxButton( this, wxID_ANY, wxT("Start Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( btnStartTest, 0, wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	mainMenuBar = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* itemFileSettings;
	itemFileSettings = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( itemFileSettings );

	menuFile->AppendSeparator();

	wxMenuItem* itemFileQuit;
	itemFileQuit = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( itemFileQuit );

	mainMenuBar->Append( menuFile, wxT("File") );

	menuHelp = new wxMenu();
	wxMenuItem* itemHelpAbout;
	itemHelpAbout = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	menuHelp->Append( itemHelpAbout );

	wxMenuItem* itemHelpLibraires;
	itemHelpLibraires = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("Libraries") ) , wxEmptyString, wxITEM_NORMAL );
	menuHelp->Append( itemHelpLibraires );

	mainMenuBar->Append( menuHelp, wxT("Help") );

	this->SetMenuBar( mainMenuBar );


	this->Centre( wxBOTH );

	// Connect Events
	btnStartTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StarterFrame::onStartTest ), NULL, this );
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( StarterFrame::onSettings ), this, itemFileSettings->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( StarterFrame::onPressQuit ), this, itemFileQuit->GetId());
	menuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( StarterFrame::onAbout ), this, itemHelpAbout->GetId());
	menuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( StarterFrame::onLibraries ), this, itemHelpLibraires->GetId());
}

StarterFrame::~StarterFrame()
{
	// Disconnect Events
	btnStartTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StarterFrame::onStartTest ), NULL, this );

}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* mainSz;
	mainSz = new wxFlexGridSizer( 2, 1, 0, 0 );
	mainSz->AddGrowableCol( 0 );
	mainSz->AddGrowableRow( 1 );
	mainSz->SetFlexibleDirection( wxBOTH );
	mainSz->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	txtAbout = new wxTextCtrl( this, wxID_ANY, wxT("PixelGames is a small minigame collection, written by 321Productions "), wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_READONLY );
	mainSz->Add( txtAbout, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* actionSz;
	actionSz = new wxGridSizer( 1, 2, 0, 0 );

	btnGitHub = new wxButton( this, wxID_ANY, wxT("View this project on GitHub"), wxDefaultPosition, wxDefaultSize, 0 );
	actionSz->Add( btnGitHub, 0, wxALL|wxEXPAND, 5 );

	btnClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	actionSz->Add( btnClose, 0, wxALL|wxEXPAND, 5 );


	mainSz->Add( actionSz, 1, wxEXPAND, 5 );


	this->SetSizer( mainSz );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	btnGitHub->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onGithub ), NULL, this );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onClose ), NULL, this );
}

AboutDialog::~AboutDialog()
{
	// Disconnect Events
	btnGitHub->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onGithub ), NULL, this );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onClose ), NULL, this );

}

LibrariesDialog::LibrariesDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* mainSz;
	mainSz = new wxFlexGridSizer( 2, 1, 0, 0 );
	mainSz->AddGrowableCol( 0 );
	mainSz->AddGrowableRow( 0 );
	mainSz->SetFlexibleDirection( wxBOTH );
	mainSz->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	nbLibs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	mainSz->Add( nbLibs, 1, wxEXPAND | wxALL, 5 );

	wxGridSizer* actionSz;
	actionSz = new wxGridSizer( 1, 3, 0, 0 );

	btnWebsite = new wxButton( this, wxID_ANY, wxT("Visit library website"), wxDefaultPosition, wxDefaultSize, 0 );
	actionSz->Add( btnWebsite, 0, wxALL|wxEXPAND, 5 );

	btnGithub = new wxButton( this, wxID_ANY, wxT("Visit library GitHub"), wxDefaultPosition, wxDefaultSize, 0 );
	actionSz->Add( btnGithub, 0, wxALL|wxEXPAND, 5 );

	btnClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	actionSz->Add( btnClose, 0, wxALL|wxEXPAND, 5 );


	mainSz->Add( actionSz, 1, wxEXPAND, 5 );


	this->SetSizer( mainSz );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	btnWebsite->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onWebsite ), NULL, this );
	btnGithub->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onGithub ), NULL, this );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onClose ), NULL, this );
}

LibrariesDialog::~LibrariesDialog()
{
	// Disconnect Events
	btnWebsite->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onWebsite ), NULL, this );
	btnGithub->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onGithub ), NULL, this );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LibrariesDialog::onClose ), NULL, this );

}

LibraryPanel::LibraryPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* szMain;
	szMain = new wxBoxSizer( wxVERTICAL );

	imgLogo = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	szMain->Add( imgLogo, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* szInfo;
	szInfo = new wxFlexGridSizer( 2, 2, 0, 0 );
	szInfo->AddGrowableCol( 0 );
	szInfo->AddGrowableCol( 1 );
	szInfo->AddGrowableRow( 1 );
	szInfo->SetFlexibleDirection( wxBOTH );
	szInfo->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	txtUsageDesc = new wxStaticText( this, wxID_ANY, wxT("Usage:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtUsageDesc->Wrap( -1 );
	szInfo->Add( txtUsageDesc, 0, wxALL, 5 );

	txtLicenseDesc = new wxStaticText( this, wxID_ANY, wxT("License:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtLicenseDesc->Wrap( -1 );
	szInfo->Add( txtLicenseDesc, 0, wxALL, 5 );

	scrollUsage = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scrollUsage->SetScrollRate( 5, 5 );
	wxGridSizer* szUsage;
	szUsage = new wxGridSizer( 1, 1, 0, 0 );

	txtUsage = new wxTextCtrl( scrollUsage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_READONLY );
	szUsage->Add( txtUsage, 0, wxALL|wxEXPAND, 5 );


	scrollUsage->SetSizer( szUsage );
	scrollUsage->Layout();
	szUsage->Fit( scrollUsage );
	szInfo->Add( scrollUsage, 1, wxEXPAND | wxALL, 5 );

	scrollLicense = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scrollLicense->SetScrollRate( 5, 5 );
	wxGridSizer* szLicense;
	szLicense = new wxGridSizer( 1, 1, 0, 0 );

	txtLicense = new wxTextCtrl( scrollLicense, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_READONLY );
	szLicense->Add( txtLicense, 0, wxALL|wxEXPAND, 5 );


	scrollLicense->SetSizer( szLicense );
	scrollLicense->Layout();
	szLicense->Fit( scrollLicense );
	szInfo->Add( scrollLicense, 1, wxEXPAND | wxALL, 5 );


	szMain->Add( szInfo, 1, wxEXPAND, 5 );


	this->SetSizer( szMain );
	this->Layout();
	szMain->Fit( this );
}

LibraryPanel::~LibraryPanel()
{
}

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


	this->Centre( wxBOTH );
}

SettingsDialog::~SettingsDialog()
{
}
