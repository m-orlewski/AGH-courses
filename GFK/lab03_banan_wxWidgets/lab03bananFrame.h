#ifndef __lab03bananFrame__
#define __lab03bananFrame__

/**
@file
Subclass of bananFrame, which is generated by wxFormBuilder.
*/

#include "lab03.h"

//// end generated include

#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/filedlg.h>

/** Implementing bananFrame */
class lab03bananFrame : public bananFrame
{
	protected:
		// Handlers for bananFrame events.
		void displayPanelOnPaint( wxPaintEvent& event );
		void displayPanelOnSize( wxSizeEvent& event );
		void saveButtonOnButtonClick( wxCommandEvent& event );
		void bananCheckBoxOnCheckBox( wxCommandEvent& event );
		void armScrollOnScroll( wxScrollEvent& event );
		void colorButtonOnButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		lab03bananFrame( wxWindow* parent );
	//// end generated class members
		~lab03bananFrame();

	private:
		int banana_move = 0;

		wxImage* banan_image = nullptr;
		wxBitmap* bitmap = nullptr;
		wxBitmap* saveBitmap = nullptr;

		wxColor star_color = wxColor("black");


};

#endif // __lab03bananFrame__
