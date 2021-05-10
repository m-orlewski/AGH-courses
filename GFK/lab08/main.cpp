#include <wx/wxprec.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MainFrame* frame = new MainFrame(nullptr);
	frame->Show(true);
	return true;
}