#include "GUIMyFrame1.h"

#include <vector>
#include <cmath>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy = Img_Org.ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy = Img_Org.Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy = Img_Org.Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy.Rescale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org.Rotate(30.0 * M_PI / 180.0, wxPoint(Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org;
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org.Copy();
	unsigned w = Img_Cpy.GetWidth();
	unsigned h = Img_Cpy.GetHeight();

	auto pixels = Img_Cpy.GetData();
	auto pixels_copy = new unsigned char[w * h * 3];
	double dx;

	for (unsigned i = 0; i < w * h * 3; i++)
		pixels_copy[i] = pixels[i];

	for (unsigned x = 1; x < w - 1; x++)
	{
		for (unsigned y = 1; y < h - 1; y++)
		{
			for (unsigned i = 0; i < 3; i++)
			{
				dx = 0;
				dx += pixels_copy[3 * ((y + 1) * w + x) + i];
				dx += pixels_copy[3 * ((y + 1) * w + x + 1) + i];
				dx += pixels_copy[3 * ((y + 1) * w + x - 1) + i];
				dx -= pixels_copy[3 * ((y - 1) * w + x ) + i];
				dx -= pixels_copy[3 * ((y - 1) * w + x + 1) + i];
				dx -= pixels_copy[3 * ((y - 1) * w + x - 1) + i];
				pixels[3 * (y * w + x) + i] = fabs(dx) / 3.0;
			}

		}
	}

	delete[] pixels_copy;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Refresh();
	Img_Cpy = Img_Org.Copy();
	int w = Img_Cpy.GetWidth();
	int h = Img_Cpy.GetHeight();
	auto pixels = Img_Cpy.GetData();

	for (int i = 0; i < w * h * 3; i++)
	{
		if (pixels[i] < 128)
			pixels[i] = 0;
		else
			pixels[i] = 255;
	}
}


void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	int w = Img_Cpy.GetWidth();
	int h = Img_Cpy.GetHeight();
	double val;
	double contrast;
	if (value != 100)
		contrast = (static_cast<double>(value) + 100.0) / (100.0 - static_cast<double>(value));
	else
		contrast = 100.0;
	auto pixels = Img_Cpy.GetData();

	for (int i = 0; i < w * h * 3; i++)
	{
		val = contrast * (pixels[i] - 127) + 127;

		if (val > 255)
			pixels[i] = 255;
		else if (val < 0)
			pixels[i] = 0;
		else
			pixels[i] = val;
	}


}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	int w = Img_Cpy.GetWidth();
	int h = Img_Cpy.GetHeight();
	auto pixels = Img_Cpy.GetData();
	int val;

	for (int i = 0; i < w * h * 3; i++)
	{
		val = pixels[i] + value;
		if (val < 0)
			val = 0;
		else if (val > 255)
			val = 255;

		pixels[i] = val;
	}
}