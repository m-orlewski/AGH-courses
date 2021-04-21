#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range()
{
    double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin = cfg->Get_x_start();
    xmax = cfg->Get_x_stop();

    step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
    x = cfg->Get_x_start();

    for (i = 0; i <= x_step; i++)
    {
        y = GetFunctionValue(x);
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x)
{
    if (cfg->Get_F_type() == 1) return x * x;
    if (cfg->Get_F_type() == 2) return 0.5 * exp(4 * x - 3 * x * x);
    return x + sin(x * 4.0);
}

void ChartClass::Draw(wxDC* dc, int w, int h)
{
    dc->SetBackground(wxBrush(RGB(255, 255, 255)));
    dc->Clear();

    dc->SetPen(wxPen(wxColour("blue")));
    Set_Range();
    
    Matrix t;
    if (cfg->RotateScreenCenter())
    {
        t = rotationMatrix(w, h) * translationMatrix() * scaleMatrix(w, h);
    }
    else
    {
        t = translationMatrix() * rotationMatrix(w, h) * scaleMatrix(w, h);
    }

    line2d(t, x_min, 0, x_max, 0, dc, w, h);
    line2d(t, 0, y_min, 0, y_max, dc, w, h);
    line2d(t, x_max, 0, x_max - 0.1, -0.1, dc, w, h);
    line2d(t, x_max, 0, x_max - 0.1, 0.1, dc, w, h);
    line2d(t, 0, y_max, -0.05, y_max - 0.2, dc, w, h);
    line2d(t, 0, y_max, 0.05, y_max - 0.2, dc, w, h);

    line2d(t, x_min / 2., 0.05, x_min / 2., -0.05, dc, w, h, true);
    line2d(t, x_max / 3., 0.05, x_max / 3., -0.05, dc, w, h, true);
    line2d(t, 2. * x_max / 3., 0.05, 2. * x_max / 3., -0.05, dc, w, h, true);
    line2d(t, 0.05, y_min / 2., -0.05, y_min / 2., dc, w, h, true, true);
    line2d(t, 0.05, y_max / 3., -0.05, y_max / 3., dc, w, h, true, true);
    line2d(t, 0.05, 2 * y_max / 3., -0.05, 2 * y_max / 3., dc, w, h, true, true);

    dc->SetPen(wxPen(wxColour("green")));
    double step = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
    double x1 = cfg->Get_x_start();
    double x2 = cfg->Get_x_stop();
    for (double x = x1; x < x2; x += step)
    {
        line2d(t, x, GetFunctionValue(x), x + step, GetFunctionValue(x + step), dc, w, h);
    }
}

void ChartClass::line2d(Matrix t, double x1, double y1, double x2, double y2, wxDC * dc, int w, int h, bool flag, bool vertical)
{
    Vector start, end;
    start.Set(x1, y1);
    end.Set(x2, y2);

    start = t * start;
    end = t * end;
    dc->DrawLine(start.GetX(), h - start.GetY(), end.GetX(), h - end.GetY());

    if (flag)
    {
        if (vertical)
            dc->DrawRotatedText(std::to_string(y1), end.GetX(), h - end.GetY(), cfg->Get_Alpha());
        else
            dc->DrawRotatedText(std::to_string(x1), end.GetX(), h - end.GetY(), cfg->Get_Alpha());
    }
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

Matrix ChartClass::translationMatrix() const
{
    Matrix m;
    m.data[0][0] = 1.0;
    m.data[1][1] = 1.0;
    m.data[0][2] = cfg->Get_dX();
    m.data[1][2] = cfg->Get_dY();

    return m;
}

Matrix ChartClass::rotationMatrix(int w, int h) const
{
    Matrix m;

    double cosinus = cos(cfg->Get_Alpha() * M_PI / 180.0);
    double sinus = sin(cfg->Get_Alpha() * M_PI / 180.0);

    m.data[0][0] = cosinus;
    m.data[1][0] = sinus;
    m.data[0][1] = -sinus;
    m.data[1][1] = cosinus;

    Matrix t1, t2;
    t1.data[0][0] = 1.0;
    t1.data[1][1] = 1.0;
    t2.data[0][0] = 1.0;
    t2.data[1][1] = 1.0;

    if (cfg->RotateScreenCenter())
    {
        t1.data[0][2] = w / 2;
        t1.data[1][2] = h / 2;
    }
    else
    {
        Matrix s = scaleMatrix(w, h);
        t1.data[0][2] = s.data[0][2];
        t1.data[1][2] = s.data[1][2];
    }

    t2.data[0][2] = -t1.data[0][2];
    t2.data[1][2] = -t1.data[1][2];

    return t1 * m * t2;
}

Matrix ChartClass::scaleMatrix(int w, int h) const
{
    Matrix m;
    m.data[0][0] = (w - 10.0) / (cfg->Get_x1() - cfg->Get_x0());
    m.data[1][1] = (h - 10.0) / (cfg->Get_y1() - cfg->Get_y0());
    m.data[0][2] = 10.0 - m.data[0][0] * cfg->Get_x0();
    m.data[1][2] = 10.0 - m.data[1][1] * cfg->Get_y0();
    return m;
}
