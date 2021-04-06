///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "lab03.h"

///////////////////////////////////////////////////////////////////////////

bananFrame::bananFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bananWindow;
	bananWindow = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* displaySizer;
	displaySizer = new wxBoxSizer( wxVERTICAL );
	
	displayPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	displayPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	displaySizer->Add( displayPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	bananWindow->Add( displaySizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* controlSizer;
	controlSizer = new wxBoxSizer( wxVERTICAL );
	
	saveButton = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	controlSizer->Add( saveButton, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bananCheckBox = new wxCheckBox( this, wxID_ANY, wxT("banan"), wxDefaultPosition, wxDefaultSize, 0 );
	controlSizer->Add( bananCheckBox, 0, wxALIGN_CENTER|wxALL, 5 );
	
	armScroll = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	controlSizer->Add( armScroll, 0, wxALIGN_CENTER|wxALL, 5 );
	
	armGauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	armGauge->SetValue( 0 ); 
	controlSizer->Add( armGauge, 0, wxALIGN_CENTER|wxALL, 5 );
	
	colorButton = new wxButton( this, wxID_ANY, wxT("Kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	controlSizer->Add( colorButton, 0, wxALIGN_CENTER|wxBOTTOM, 5 );
	
	displayText = new wxTextCtrl( this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0 );
	controlSizer->Add( displayText, 0, wxALIGN_CENTER|wxALL, 5 );
	
	wxString shapeChoiceChoices[] = { wxT("gwiazdka"), wxT("księżyc"), wxT("słonko") };
	int shapeChoiceNChoices = sizeof( shapeChoiceChoices ) / sizeof( wxString );
	shapeChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, shapeChoiceNChoices, shapeChoiceChoices, 0 );
	shapeChoice->SetSelection( 0 );
	controlSizer->Add( shapeChoice, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bananWindow->Add( controlSizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bananWindow );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	displayPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( bananFrame::displayPanelOnPaint ), NULL, this );
	displayPanel->Connect( wxEVT_SIZE, wxSizeEventHandler( bananFrame::displayPanelOnSize ), NULL, this );
	saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bananFrame::saveButtonOnButtonClick ), NULL, this );
	bananCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( bananFrame::bananCheckBoxOnCheckBox ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	colorButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bananFrame::colorButtonOnButtonClick ), NULL, this );
}

bananFrame::~bananFrame()
{
	// Disconnect Events
	displayPanel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( bananFrame::displayPanelOnPaint ), NULL, this );
	displayPanel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( bananFrame::displayPanelOnSize ), NULL, this );
	saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bananFrame::saveButtonOnButtonClick ), NULL, this );
	bananCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( bananFrame::bananCheckBoxOnCheckBox ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	armScroll->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( bananFrame::armScrollOnScroll ), NULL, this );
	colorButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bananFrame::colorButtonOnButtonClick ), NULL, this );
	
}
