///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __LAB03_H__
#define __LAB03_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class bananFrame
///////////////////////////////////////////////////////////////////////////////
class bananFrame : public wxFrame 
{
	private:
	
	protected:
		wxPanel* displayPanel;
		wxButton* saveButton;
		wxCheckBox* bananCheckBox;
		wxScrollBar* armScroll;
		wxGauge* armGauge;
		wxButton* colorButton;
		wxTextCtrl* displayText;
		wxChoice* shapeChoice;
		
		// Virtual event handlers, overide them in your derived class
		virtual void displayPanelOnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void displayPanelOnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void saveButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void bananCheckBoxOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void armScrollOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void colorButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		bananFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GFK Lab 03"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 874,595 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~bananFrame();
	
};

#endif //__LAB03_H__
