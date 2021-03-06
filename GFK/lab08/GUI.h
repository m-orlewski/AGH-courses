///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI
///////////////////////////////////////////////////////////////////////////////
class GUI : public wxFrame 
{
	private:
	
	protected:
		wxButton* LoadFileButton;
		wxButton* BlurButton;
		wxButton* ErodeButton;
		wxCheckBox* AnimationCheckBox;
		wxTextCtrl* TextControl;
		wxPanel* DisplayPanel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void IdleEvent( wxIdleEvent& event ) { event.Skip(); }
		virtual void LoadFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void BlurFace( wxCommandEvent& event ) { event.Skip(); }
		virtual void Erode( wxCommandEvent& event ) { event.Skip(); }
		virtual void Animation( wxCommandEvent& event ) { event.Skip(); }
		virtual void DisplayPanelOnSize( wxSizeEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUI();
	
};

#endif //__GUI_H__
