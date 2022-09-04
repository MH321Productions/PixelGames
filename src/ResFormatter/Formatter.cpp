///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Formatter.h"

///////////////////////////////////////////////////////////////////////////

FormatterFrame::FormatterFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSz;
	fgSz = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSz->AddGrowableCol( 0 );
	fgSz->AddGrowableRow( 1 );
	fgSz->SetFlexibleDirection( wxBOTH );
	fgSz->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxGridSizer* btnSz;
	btnSz = new wxGridSizer( 1, 2, 0, 0 );

	btnLoad = new wxButton( this, wxID_ANY, wxT("Load resource file"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSz->Add( btnLoad, 0, wxALL|wxEXPAND, 5 );

	btnSave = new wxButton( this, wxID_ANY, wxT("Save resource file"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSz->Add( btnSave, 0, wxALL|wxEXPAND, 5 );


	fgSz->Add( btnSz, 1, wxEXPAND, 5 );

	scroll = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scroll->SetScrollRate( 5, 5 );
	wxBoxSizer* resSz;
	resSz = new wxBoxSizer( wxVERTICAL );


	scroll->SetSizer( resSz );
	scroll->Layout();
	resSz->Fit( scroll );
	fgSz->Add( scroll, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( fgSz );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	btnLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onLoad ), NULL, this );
	btnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onSave ), NULL, this );
}

FormatterFrame::~FormatterFrame()
{
	// Disconnect Events
	btnLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onLoad ), NULL, this );
	btnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onSave ), NULL, this );

}

ResEntryPanel::ResEntryPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
}

ResEntryPanel::~ResEntryPanel()
{
}
