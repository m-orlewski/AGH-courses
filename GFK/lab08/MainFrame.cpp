#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent)
	:
	GUI(parent)
{
	image.AddHandler(new wxJPEGHandler);

	timer = new wxTimer();
	timer->SetOwner(this, 1001);
	Bind(wxEVT_TIMER, &MainFrame::DisplayAnimation, this, 1001);
}

void MainFrame::IdleEvent(wxIdleEvent& event)
{
	if (resized)
	{
		int x, y;
		DisplayPanel->GetSize(&x, &y);
		image.Rescale(x, y);
		if (copy.IsOk())
			copy.Rescale(x, y);
		else
			copy = image.Copy();
		bitmap = wxBitmap(copy);
		resized = false;
		Draw();
	}
}

void MainFrame::LoadFile(wxCommandEvent& event)
{
	int w, h;
	std::shared_ptr<wxFileDialog> WxOpenFileDialog1(new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN));
	if (WxOpenFileDialog1->ShowModal() == wxID_OK)
	{
		if (!image.LoadFile(WxOpenFileDialog1->GetPath(), wxBITMAP_TYPE_JPEG))
		{
			wxLogError(_("Nie mo¿na za³adowaæ obrazka"));
		}
		else
		{
			int x, y;
			w = image.GetWidth();
			h = image.GetHeight();
			DisplayPanel->GetSize(&x, &y);
			image.Rescale(x, y);
			copy = image.Copy();
			bitmap = wxBitmap(image);
		}
		if (bitmap.Ok())
		{
			this->SetTitle(WxOpenFileDialog1->GetPath());
			Draw();
			ExifInfo(WxOpenFileDialog1->GetPath(), w, h);
		}
	}
}

void MainFrame::BlurFace(wxCommandEvent& event)
{

	copy = image.Copy();
	int w, h;
	w = image.GetWidth();
	h = image.GetHeight();
	int face_w, face_h;
	face_w = 0.15 * w;
	face_h = 0.15 * h;
	int face_x, face_y;
	face_x = 0.57 * w;
	face_y = 0.04 * h;

	CImg<unsigned char>img(face_w, face_h, 1, 3);

	for (int i = 0; i < face_w; i++)
	{
		for (int j = 0; j < face_h; j++)
		{
			img(i, j, 0) = image.GetRed(face_x + i, face_y + j);
			img(i, j, 1) = image.GetGreen(face_x + i, face_y + j);
			img(i, j, 2) = image.GetBlue(face_x + i, face_y + j);
		}
	}

	img.blur(5.0);

	for (int i = 0; i < face_w; i++)
	{
		for (int j = 0; j < face_h; j++)
		{
			copy.SetRGB(face_x + i, face_y + j, img(i, j, 0), img(i, j, 1), img(i, j, 2));
		}
	}
	bitmap = wxBitmap(copy);
	Draw();
}

void MainFrame::Erode(wxCommandEvent& event)
{
	copy = image.Copy();

	int w, h;
	w = image.GetWidth();
	h = image.GetHeight();

	CImg<unsigned char>img(w, h, 1, 3);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			img(i, j, 0) = image.GetRed(i, j);
			img(i, j, 1) = image.GetGreen(i, j);
			img(i, j, 2) = image.GetBlue(i, j);
		}
	}

	img.erode(10, 10);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			copy.SetRGB(i, j, img(i, j, 0), img(i, j, 1), img(i, j, 2));
		}
	}
	bitmap = wxBitmap(copy);
	Draw();
}

void MainFrame::Animation(wxCommandEvent& event)
{
	if (AnimationCheckBox->IsChecked())
	{
		PrepareAnimations();
		i = 0;
		timer->Start(50);
	}
	else
	{
		timer->Stop();
		delete[] animations;
		Draw();
	}
}

void MainFrame::DisplayPanelOnSize(wxSizeEvent& event)
{
	if (bitmap.IsOk())
	{
		resized = true;
	}
}


void MainFrame::ExifInfo(const char* file_name, int w, int h)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(file_name, 0);

	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(file_name);

	if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif))
	{
		FIBITMAP* FI_bitmap = FreeImage_Load(fif, file_name, 0);
		FITAG* tag = nullptr;
		FIMETADATA* mdhandle = nullptr;
		FREE_IMAGE_MDMODEL model = FIMD_EXIF_MAIN;

		mdhandle = FreeImage_FindFirstMetadata(model, FI_bitmap, &tag);
		*TextControl << "Rozmiar obrazka: " << w << "*" << h << "\n";
		*TextControl << "EXIF Info:\n";
		do
		{
			const char* value = FreeImage_TagToString(model, tag);
			*TextControl << FreeImage_GetTagKey(tag) << ": " << value << "\n";
		} while (FreeImage_FindNextMetadata(mdhandle, &tag));
	}
}

void MainFrame::DisplayAnimation(wxTimerEvent& e)
{
	wxClientDC dc(DisplayPanel);
	dc.Clear();
	dc.DrawBitmap(animations[i], 0, 0);

	i++;
	if (i == 37)
		i = 0;
}

void MainFrame::PrepareAnimations()
{
	copy = image.Copy();

	animations = new wxBitmap[37];

	int w, h;
	w = image.GetWidth();
	h = image.GetHeight();

	CImg<unsigned char>img(w, h, 1, 3);
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			img(i, j, 0) = image.GetRed(i, j);
			img(i, j, 1) = image.GetGreen(i, j);
			img(i, j, 2) = image.GetBlue(i, j);
		}
	}

	float color[3] = { 1.0f, 1.0f, 1.0f };
	int t2;
	int id = 0;
	for (int t = 0; t <= 360; t += 10)
	{
		CImg<unsigned char>img_copy(img);
		t2 = (t + 180) % 360;

		cimg_library::CImg<float> mask1(w, h, 1, 3);
		cimg_library::CImg<float> mask2(w, h, 1, 3);

		mask1.draw_gaussian(w / 2 + (w * 0.2) * cos(t * M_PI / 180.0), h / 2 + (h * 0.2) * sin(t * M_PI / 180.0), 80.0f, color, 1.0f);
		mask2.draw_gaussian(w / 2 + (w * 0.2) * cos(t2 * M_PI / 180.0), h / 2 + (h * 0.2) * sin(t2 * M_PI / 180.0), 80.0f, color, 1.0f);

		img_copy.mul(mask1 + mask2);

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				copy.SetRGB(i, j, img_copy(i, j, 0), img_copy(i, j, 1), img_copy(i, j, 2));
			}
		}

		animations[id++] = wxBitmap(copy);
	}
	copy = image.Copy();
}

void MainFrame::Draw()
{
	wxClientDC dc(DisplayPanel);
	dc.Clear();
	dc.DrawBitmap(bitmap, 0, 0);
}