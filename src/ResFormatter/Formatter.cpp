///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
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
	btnSz = new wxGridSizer( 1, 3, 0, 0 );

	btnLoad = new wxButton( this, wxID_ANY, wxT("Load resource file"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSz->Add( btnLoad, 0, wxALL|wxEXPAND, 5 );

	btnSave = new wxButton( this, wxID_ANY, wxT("Save resource file"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSz->Add( btnSave, 0, wxALL|wxEXPAND, 5 );

	btnNew = new wxButton( this, wxID_ANY, wxT("Add Resource"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSz->Add( btnNew, 0, wxALL|wxEXPAND, 5 );


	fgSz->Add( btnSz, 1, wxEXPAND, 5 );

	scroll = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scroll->SetScrollRate( 5, 5 );
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
	btnNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onAdd ), NULL, this );
}

FormatterFrame::~FormatterFrame()
{
	// Disconnect Events
	btnLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onLoad ), NULL, this );
	btnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onSave ), NULL, this );
	btnNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FormatterFrame::onAdd ), NULL, this );

}

ResEntryPanel::ResEntryPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxFlexGridSizer* entrySz;
	entrySz = new wxFlexGridSizer( 1, 8, 0, 0 );
	entrySz->AddGrowableCol( 1 );
	entrySz->AddGrowableCol( 5 );
	entrySz->AddGrowableRow( 0 );
	entrySz->SetFlexibleDirection( wxBOTH );
	entrySz->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	lblName = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblName->Wrap( -1 );
	entrySz->Add( lblName, 0, wxALIGN_CENTER|wxALL, 5 );

	txtName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	entrySz->Add( txtName, 0, wxALL|wxEXPAND, 5 );

	lblType = new wxStaticText( this, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblType->Wrap( -1 );
	entrySz->Add( lblType, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString choiceTypeChoices[] = { wxT("Undefined"), wxT("Text"), wxT("Number"), wxT("Binary") };
	int choiceTypeNChoices = sizeof( choiceTypeChoices ) / sizeof( wxString );
	choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceTypeNChoices, choiceTypeChoices, 0 );
	choiceType->SetSelection( 0 );
	entrySz->Add( choiceType, 0, wxALIGN_CENTER|wxALL, 5 );

	lblValue = new wxStaticText( this, wxID_ANY, wxT("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblValue->Wrap( -1 );
	entrySz->Add( lblValue, 0, wxALIGN_CENTER|wxALL, 5 );

	txtValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtValue->Enable( false );

	entrySz->Add( txtValue, 0, wxALL|wxEXPAND, 5 );

	btnValue = new wxButton( this, wxID_ANY, wxT("Open File"), wxDefaultPosition, wxDefaultSize, 0 );
	btnValue->Enable( false );

	entrySz->Add( btnValue, 0, wxALL|wxEXPAND, 5 );

	btnDelete = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	entrySz->Add( btnDelete, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( entrySz );
	this->Layout();

	// Connect Events
	choiceType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ResEntryPanel::onType ), NULL, this );
	btnValue->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResEntryPanel::onBinary ), NULL, this );
	btnDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResEntryPanel::onDelete ), NULL, this );
}

ResEntryPanel::~ResEntryPanel()
{
	// Disconnect Events
	choiceType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ResEntryPanel::onType ), NULL, this );
	btnValue->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResEntryPanel::onBinary ), NULL, this );
	btnDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResEntryPanel::onDelete ), NULL, this );

}
