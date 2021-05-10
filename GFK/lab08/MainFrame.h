#ifndef __MainFrame__
#define __MainFrame__

/**
@file
Subclass of GUI, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

#include <wx/wxprec.h>
#include <cmath>

#include "CImg.h"
#include "FreeImage.h"

using namespace cimg_library;

/** Implementing GUI */
class MainFrame : public GUI
{
	protected:
		// Handlers for GUI events.
		void IdleEvent( wxIdleEvent& event );
		void LoadFile( wxCommandEvent& event );
		void BlurFace( wxCommandEvent& event );
		void Erode( wxCommandEvent& event );
		void Animation( wxCommandEvent& event );
		void DisplayPanelOnSize( wxSizeEvent& event );
	public:
		/** Constructor */
		MainFrame( wxWindow* parent );
	//// end generated class members

	protected:
		wxImage image;
		wxImage copy;
		wxBitmap bitmap;
		FIBITMAP fi_bitmap;
		wxTimer* timer = nullptr;
		wxBitmap* animations;
		int i = 0;
		bool resized = false;
	public:
		void Draw();
		void ExifInfo(const char* file_name, int w, int h);
		void DisplayAnimation(wxTimerEvent& e);
		void PrepareAnimations();

};

#endif // __MainFrame__
