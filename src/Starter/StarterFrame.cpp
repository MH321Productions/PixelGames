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

	this->Centre( wxBOTH );

	// Connect Events
	btnStartTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StarterFrame::onStartTest ), NULL, this );
}

StarterFrame::~StarterFrame()
{
	// Disconnect Events
	btnStartTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StarterFrame::onStartTest ), NULL, this );

}
