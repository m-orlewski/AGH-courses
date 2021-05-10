///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

GUI::GUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	bSizer2->SetMinSize( wxSize( 200,-1 ) ); 
	LoadFileButton = new wxButton( this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( LoadFileButton, 0, wxALIGN_CENTER|wxALL, 5 );
	
	BlurButton = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( BlurButton, 0, wxALIGN_CENTER|wxALL, 5 );
	
	ErodeButton = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ErodeButton, 0, wxALIGN_CENTER|wxALL, 5 );
	
	AnimationCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Animation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( AnimationCheckBox, 0, wxALIGN_CENTER|wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	TextControl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_MULTILINE|wxTE_NO_VSCROLL );
	bSizer5->Add( TextControl, 1, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	DisplayPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 800,533 ), wxTAB_TRAVERSAL );
	DisplayPanel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	DisplayPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	
	bSizer3->Add( DisplayPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( GUI::IdleEvent ) );
	LoadFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::LoadFile ), NULL, this );
	BlurButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::BlurFace ), NULL, this );
	ErodeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::Erode ), NULL, this );
	AnimationCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUI::Animation ), NULL, this );
	DisplayPanel->Connect( wxEVT_SIZE, wxSizeEventHandler( GUI::DisplayPanelOnSize ), NULL, this );
}

GUI::~GUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUI::IdleEvent ) );
	LoadFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::LoadFile ), NULL, this );
	BlurButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::BlurFace ), NULL, this );
	ErodeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::Erode ), NULL, this );
	AnimationCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUI::Animation ), NULL, this );
	DisplayPanel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUI::DisplayPanelOnSize ), NULL, this );
	
}
