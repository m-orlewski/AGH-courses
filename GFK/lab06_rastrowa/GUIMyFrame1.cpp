#include "GUIMyFrame1.h"

#include <vector>
#include <cmath>

void rgb_to_hsl(double * rgb)
{

	double var_R = (rgb[0] / 255);
	double var_G = (rgb[1] / 255);
	double var_B = (rgb[2] / 255);

	double var_Min = (var_R < var_G) ? ((var_R < var_B) ? var_R : var_B) : ((var_G < var_B) ? var_G : var_B);
	double var_Max = (var_R > var_G) ? ((var_R > var_B) ? var_R : var_B) : ((var_G > var_B) ? var_G : var_B);
	double del_Max = var_Max - var_Min;           //Delta RGB value

	double L = (var_Max + var_Min) / 2;

	double H, S, del_R, del_G, del_B;

		if (del_Max == 0)                     //This is a gray, no chroma...
		{
			H = 0;
			S = 0;
		}
		else                                    //Chromatic data...
		{
			if (L < 0.5)
				S = del_Max / (var_Max + var_Min);
			else
				S = del_Max / (2 - var_Max - var_Min);

			del_R = (((var_Max - var_R) / 6) + (del_Max / 2)) / del_Max;
			del_G = (((var_Max - var_G) / 6) + (del_Max / 2)) / del_Max;
			del_B = (((var_Max - var_B) / 6) + (del_Max / 2)) / del_Max;

			if (var_R == var_Max)
				H = del_B - del_G;
			else if (var_G == var_Max)
				H = (1 / 3) + del_R - del_B;
			else if (var_B == var_Max)
				H = (2 / 3) + del_G - del_R;

			if (H < 0)
				H += 1;
			if (H > 1)
				H -= 1;
		}
		rgb[0] = H;
		rgb[1] = S;
		rgb[2] = L;
}

double Hue_2_RGB(double v1, double v2, double vH);

void hsl_to_rgb(double* hsl)
{
	double H = hsl[0];
	double S = hsl[1];
	double L = hsl[2];

	double R, G, B, var_2, var_1;

	if (S == 0)
	{

		R = L * 255;
		G = L * 255;
		B = L * 255;
	}
	else
	{
		if (L < 0.5)
			var_2 = L * (1 + S);
		else
			var_2 = (L + S) - (S * L);

		var_1 = 2 * L - var_2;

		R = 255 * Hue_2_RGB(var_1, var_2, H + (1 / 3));
		G = 255 * Hue_2_RGB(var_1, var_2, H);
		B = 255 * Hue_2_RGB(var_1, var_2, H - (1 / 3));
	}
}

double Hue_2_RGB(double v1, double v2, double vH)
{
	if (vH < 0)
		vH += 1;
			
	if (vH > 1)
		vH -= 1;
				
	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);
					
	if ((2 * vH) < 1)
		return (v2);
						
	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2 / 3) - vH) * 6);

	return (v1);
}

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

	auto pixels1 = Img_Cpy.GetData();
	std::vector<unsigned char> pixels_copy;
	double dx;

	for (unsigned i = 0; i < w * h * 3; i++)
		pixels_copy.push_back(pixels1[i]);

	for (unsigned x = 1; x < w - 1; x++)
	{
		for (unsigned y = 1; y < h - 1; y++)
		{
			for (unsigned i = 0; i < 3; i++)
			{
				dx = 0;
				dx += pixels_copy[i + y * 3 * w + 3 * (x + 1)];
				dx -= pixels_copy[i + y * 3 * w + 3 * (x - 1)];
				dx += pixels_copy[i + (y + 1) * 3 * w + 3 * (x + 1)];
				dx -= pixels_copy[i + (y + 1) * 3 * w + 3 * (x - 1)];
				dx += pixels_copy[i + (y - 1) * 3 * w + 3 * (x + 1)];
				dx -= pixels_copy[i + (y - 1) * 3 * w + 3 * (x - 1)];
				pixels1[i + y * 3U * w + 3U * x] = fabs(dx);
			}

		}
	}

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
	Refresh();
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
	Refresh();
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