#include <wx/wx.h>

#include "lab03bananFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit()
	{
		return 0;
	}
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxFrame* mainFrame = new lab03bananFrame(nullptr);
	mainFrame->Show(true);
	SetTopWindow(mainFrame);
	return true;
}