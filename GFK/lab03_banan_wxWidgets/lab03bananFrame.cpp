#include "lab03bananFrame.h"

lab03bananFrame::lab03bananFrame( wxWindow* parent )
:
bananFrame( parent )
{
	displayPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);

	wxImage::AddHandler(new wxPNGHandler());
	banan_image = new wxImage(wxSize(50, 38));
	banan_image->LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	bitmap = new wxBitmap(*banan_image);

	armScroll->SetScrollbar(0, 1, 100, 1);
	armScroll->Enable(false);
	Bind(wxEVT_COMMAND_CHOICE_SELECTED, [&, this](wxCommandEvent& e) { Refresh(); });
	Bind(wxEVT_COMMAND_TEXT_UPDATED, [&, this](wxCommandEvent& e) { Refresh(); });
}

void lab03bananFrame::displayPanelOnPaint( wxPaintEvent& event )
{
	int x, y;
	displayPanel->GetClientSize(&x, &y);
	x /= 2;
	y /= 2;
	wxAutoBufferedPaintDC buffered_dc(displayPanel);
	buffered_dc.SetBackground(wxBrush(wxColour("white")));
	buffered_dc.Clear();

	if ((*bitmap).IsOk() && bananCheckBox->GetValue())
	{
		buffered_dc.DrawBitmap(*bitmap, x - 65, y + 30 - banana_move);
	}

	buffered_dc.DrawCircle(x, y - 90, 40); //head
	buffered_dc.DrawCircle(x - 15, y - 105, 5); //left eye
	buffered_dc.DrawCircle(x + 15, y - 105, 5); //right eye
	buffered_dc.DrawLine(x, y - 50, x, y + 50); //body
	buffered_dc.DrawLine(x, y + 50, x - 20, y + 200); //left leg
	buffered_dc.DrawLine(x, y + 50, x + 20, y + 200); //right leg
	buffered_dc.DrawLine(x, y, x - 49, y + 50 - banana_move); //left arm
	buffered_dc.DrawLine(x, y, x + 49, y + 50); //right arm

	if (bananCheckBox->GetValue())
		buffered_dc.DrawEllipticArc(x - 20, y - 90, 40, 30, 0.0, -180.0); //smile
	else
		buffered_dc.DrawEllipticArc(x - 20, y - 80, 40, 30, 0.0, 180.0); //smile

	if (shapeChoice->GetSelection() == 0)
	{
		// star
		buffered_dc.SetPen(wxPen(star_color, 1, wxTRANSPARENT));
		buffered_dc.SetBrush(wxBrush(star_color, wxSOLID));
		wxPoint star[] = { {100, 100}, {120, 100}, {125, 80}, {130, 100}, {150, 100}, {135, 110}, {145, 130}, {125, 116}, {105, 130}, {115, 110} };
		buffered_dc.DrawPolygon(10, star, x - 300, y - 290);
	}
	else if (shapeChoice->GetSelection() == 1)
	{
		// moon
		buffered_dc.SetPen(wxPen(wxColor("grey"), 1, wxTRANSPARENT));
		buffered_dc.SetBrush(wxBrush(wxColor("grey"), wxSOLID));
		buffered_dc.DrawCircle(x - 200, y - 190, 30);
		buffered_dc.SetBrush(wxBrush(wxColor("white"), wxSOLID));
		buffered_dc.DrawCircle(x - 215, y - 200, 30);
	}
	else if (shapeChoice->GetSelection() == 2)
	{
		// sun
		buffered_dc.SetPen(wxPen(wxColor("yellow"), 1, wxTRANSPARENT));
		buffered_dc.SetBrush(wxBrush(wxColor("yellow"), wxSOLID));
		buffered_dc.DrawCircle(x - 200, y - 190, 30);
	}

	buffered_dc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false));
	buffered_dc.DrawText(displayText->GetLineText(0), x - 200, y + 10);

	buffered_dc.SetFont(wxFont(25, wxSWISS, wxITALIC, wxBOLD, false));
	buffered_dc.DrawRotatedText(displayText->GetLineText(0), x + 100, y + 110, 90);
}

void lab03bananFrame::displayPanelOnSize( wxSizeEvent& event )
{
	Refresh();
}

void lab03bananFrame::saveButtonOnButtonClick( wxCommandEvent& event )
{
	wxClientDC dc(displayPanel);
	wxInitAllImageHandlers();
	wxString fileName;

	wxFileDialog saveFileDialog(this, _("Choose a file"), "", "",
	"All files (*.)|*.", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	fileName = saveFileDialog.GetPath();

	wxSize panelSize = displayPanel->GetVirtualSize();
	saveBitmap = new wxBitmap((*displayPanel).GetClientSize());

	wxMemoryDC memory;
	memory.SelectObject(*saveBitmap);
	memory.Blit(0, 0, panelSize.GetX(), panelSize.GetY(), &dc, 0, 0, wxCOPY, true);

	wxImage result = saveBitmap->ConvertToImage();
	result.SaveFile(fileName, wxBITMAP_TYPE_JPEG);
}

void lab03bananFrame::bananCheckBoxOnCheckBox( wxCommandEvent& event )
{
	if (bananCheckBox->GetValue())
	{
		armScroll->Enable(true);
	}
	else
	{
		armScroll->Enable(false);
	}
	Refresh();
}

void lab03bananFrame::armScrollOnScroll( wxScrollEvent& event )
{
	banana_move = armScroll->GetThumbPosition();
	armGauge->SetValue(banana_move);
	Refresh();
}

void lab03bananFrame::colorButtonOnButtonClick( wxCommandEvent& event )
{
	wxColourDialog colour(this);
	if (colour.ShowModal() == wxID_OK)
		star_color = colour.GetColourData().GetColour();
	Refresh();
}


lab03bananFrame::~lab03bananFrame()
{
	delete banan_image;
	delete bitmap;
}