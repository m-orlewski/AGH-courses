#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include <cmath>
#include "vecmat.h"

#include <wx/dcbuffer.h>

struct Point {
    float x, y, z;
    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
    int R, G, B;
    Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
    Point begin, end;
    Color color;
    Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

Matrix4 rotationMatrixX(double x);
Matrix4 rotationMatrixY(double x);
Matrix4 rotationMatrixZ(double x);
Matrix4 scaleMatrix(double dx, double dy, double dz);
Matrix4 translationMatrix(double dx, double dy, double dz);
Matrix4 perspectiveViewMatrix(int w, int h);

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
    :
    MyFrame1(parent)
{
    m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
    m_staticText25->SetLabel(_("Obr\u00F3t X:"));
    m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
    m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

    WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
    WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
    WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

    WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
    WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
    WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

    WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
    WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
    WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);

    WxPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent& event)
{
    Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click(wxCommandEvent& event)
{
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK)
    {
        double x1, y1, z1, x2, y2, z2;
        int r, g, b;

        std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
        if (in.is_open())
        {
            data.clear();
            while (!in.eof())
            {
                in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
                data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
            }
            in.close();
        }
    }
}

void GUIMyFrame1::Scrolls_Updated(wxScrollEvent& event)
{
    WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (static_cast<double>(WxSB_TranslationX->GetValue()) - 100) / 50.0));
    WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (static_cast<double>(WxSB_TranslationY->GetValue()) - 100) / 50.0));
    WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (static_cast<double>(WxSB_TranslationZ->GetValue()) - 100) / 50.0));

    WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
    WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
    WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

    WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
    WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
    WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


    Repaint();
}


void GUIMyFrame1::Repaint()
{
    int w, h;
    WxPanel->GetClientSize(&w, &h);

    wxClientDC dc(WxPanel);
    wxBufferedDC buffered_dc(&dc);

    buffered_dc.SetBackground(wxBrush(wxColour("white")));
    buffered_dc.Clear();

    Matrix4 scale = scaleMatrix(1.0 * w  / h * WxSB_ScaleX->GetValue() / 100.0, 1.0 *  WxSB_ScaleY->GetValue() / 100.0,  WxSB_ScaleZ->GetValue() / 100.0);
    Matrix4 rotation = rotationMatrixX(WxSB_RotateX->GetValue()) * rotationMatrixY(WxSB_RotateY->GetValue()) * rotationMatrixZ(WxSB_RotateZ->GetValue());
    Matrix4 translation = translationMatrix((WxSB_TranslationX->GetValue() - 100.0 ) / 100.0, (WxSB_TranslationY->GetValue() - 100.0) / 100.0, (WxSB_TranslationZ->GetValue() + 100.0) / 100.0);
    Matrix4 perspective = perspectiveViewMatrix(w, h);

    Matrix4 t = perspective * translation * rotation * scale;

    for (auto& x : data)
    {
        Vector4 start, end;
        start.Set(x.begin.x, x.begin.y, x.begin.z);
        end.Set(x.end.x, x.end.y, x.end.z);

        start = t * start;
        end = t * end;
        
        start.data[0] /= start.data[3];
        start.data[1] /= start.data[3];

        end.data[0] /= end.data[3];
        end.data[1] /= end.data[3];
        
            buffered_dc.SetPen(wxPen(wxColour(x.color.R, x.color.G, x.color.B)));
            buffered_dc.DrawLine(start.GetX() * w + w / 2, start.GetY() * h + h / 2, end.GetX() * w + w / 2, end.GetY() * h + h / 2);
    }
}

Matrix4 scaleMatrix(double dx, double dy, double dz)
{
    Matrix4 m;
    m.data[0][0] = dx;
    m.data[1][1] = dy;
    m.data[2][2] = dz;

    return m;
}

Matrix4 translationMatrix(double dx, double dy, double dz)
{
    Matrix4 m;
    m.data[0][0] = 1.0;
    m.data[1][1] = 1.0;
    m.data[2][2] = 1.0;
    m.data[0][3] = dx;
    m.data[1][3] = -dy;
    m.data[2][3] = dz;

    return m;
}

Matrix4 rotationMatrixX(double x)
{
    x *= M_PI / 180.0;
    double cosinus = cos(x);
    double sinus = sin(x);

    Matrix4 m;
    m.data[0][0] = 1.0;
    m.data[1][1] = cosinus;
    m.data[1][2] = -sinus;
    m.data[2][1] = sinus;
    m.data[2][2] = cosinus;

    return m;
}

Matrix4 rotationMatrixY(double x)
{
    x *= -M_PI / 180.0;
    double cosinus = cos(x);
    double sinus = sin(x);

    Matrix4 m;
    m.data[0][0] = cosinus;
    m.data[1][1] = 1.0;
    m.data[0][2] = sinus;
    m.data[2][0] = -sinus;
    m.data[2][2] = cosinus;

    return m;
}

Matrix4 rotationMatrixZ(double x)
{
    x *= M_PI / 180.0;
    double cosinus = cos(x);
    double sinus = sin(x);

    Matrix4 m;
    m.data[0][0] = m.data[1][1] = cosinus;
    m.data[0][1] = -sinus;
    m.data[1][0] = sinus;
    m.data[2][2] = 1.0;

    return m;
}

Matrix4 perspectiveViewMatrix(int w, int h)
{
    //V.1
    double a, f, z_far, z_near;
    a = static_cast<double>(h) / static_cast<double>(w);
    f = 1.0 / tan(90.0f * M_PI / 360.0);
    z_near = 1.0;
    z_far = 1000.0;
    Matrix4 m;
    m.data[0][0] = a * f;
    m.data[1][1] = f;
    m.data[2][2] = (-z_near - z_far) / (z_near - z_far);
    m.data[2][3] = (2 * z_far * z_near) / (z_near - z_far);
    m.data[3][2] = 1.0;
    m.data[3][3] = 0.0;

    return m;

    //V.2
    /*
    Matrix4 m;
    double l, r, t, b, n, f;
    n = 1;
    f = 5;
    t = 0.27;
    b = -0.27;
    l = -0.43;
    r = 0.43;
    m.data[0][0] = 2 * n / (r - l);
    m.data[0][2] = (r + l) / (r - l);
    m.data[1][1] = 2 * n / (t - b);
    m.data[1][2] = (t + b) / (t - b);
    m.data[2][2] = (f + n) / (n - f);
    m.data[2][3] = 2 * f * n / (n - f);
    m.data[3][2] = -1.0;
    m.data[3][3] = 0.0;
    return m;
    */
}