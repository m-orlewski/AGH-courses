#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

#include <cmath>
#include <array>
#include <vector>

float shepard(float i, float j, float d[100][3], int N);

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
    wxMemoryDC memDC;
    memDC.SelectObject(MemoryBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();

    // demo.....
    memDC.SetPen(*wxBLACK_PEN);
    memDC.SetBrush(*wxTRANSPARENT_BRUSH);

    std::array<std::array<float, 500>, 500> grid;
    

    float f_max, f_min;
    f_min = f_max = d[0][2];
    for (int i = 0; i < N; i++)
    {
        if (d[i][2] < f_min)
            f_min = d[i][2];
        if (d[i][2] > f_max)
            f_max = d[i][2];
    }

    for (int x = 0; x < 500; x++)
        for (int y = 0; y < 500; y++)
            grid[y][x] = shepard(y, -x, d, N);

    if (MappingType)
    {
        unsigned char* bits = new unsigned char[750000]{0};
        for (int i = 0; i < 500; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                int w = 255 - (grid[i][j] - f_min) / (f_max - f_min) * 255;
                int y = j;
                switch (MappingType)
                {
                case 1:
                    //memDC.SetPen(wxPen(wxColour(w, 0, 255 - w)));
                    bits[3 * (i + 500 * y)] = w;
                    bits[3 * (i + 500 * y) + 1] = 0;
                    bits[3 * (i + 500 * y) + 2] = 255 - w;
                    break;
                case 2:
                    if (w <= 255 / 2)
                    {
                        //memDC.SetPen(wxPen(wxColour(0, 2 * w, 255 - 2 * w)));
                        bits[3 * (i + 500 * y)] = 0;
                        bits[3 * (i + 500 * y) + 1] = 2 * w;
                        bits[3 * (i + 500 * y) + 2] = 255 - 2 * w;
                    }
                    else
                    {
                        //memDC.SetPen(wxPen(wxColour(0.5 * w, 2 * (255 - w), 0)));
                        bits[3 * (i + 500 * y)] = 0.5 * w;
                        bits[3 * (i + 500 * y) + 1] = 2 * (255 - w);
                        bits[3 * (i + 500 * y) + 2] = 0;
                    }
                    break;
                case 3:
                    //memDC.SetPen(wxPen(wxColour(w, w, w)));
                    bits[3 * (i + 500 * y)] = 255-w;
                    bits[3 * (i + 500 * y) + 1] = 255-w;
                    bits[3 * (i + 500 * y) + 2] = 255-w;
                    break;
                }
            }
        }
        wxImage img(500, 500, bits);
        wxBitmap color_map(img);
        memDC.DrawBitmap(color_map, 0, 0);
    }

    if (Contour)
    {
        memDC.SetPen(wxPen(wxColour("black")));
        memDC.SetBrush(*wxTRANSPARENT_BRUSH);
        for (int i = 0; i < NoLevels; i++)
        {
            float poziomica = f_min + (i + 1) * (f_max - f_min) / (NoLevels + 1.0);
            for (int x = 0; x < 500; x++)
            {
                for (int y = 0; y < 500; y++)
                {
                    int sum = 0;
                    if (grid[x][y] >= poziomica)
                        sum += 8;
                    if (x + 2 < 500 && grid[x + 2][y] >= poziomica)
                        sum += 4;
                    if (y + 2 < 500 && grid[x][y + 2] >= poziomica)
                        sum += 1;
                    if (x + 2 < 500 && y + 2 < 500 && grid[x + 2][y + 2] >= poziomica)
                        sum += 2;

                    if (sum == 1 || sum == 14)
                    {
                        memDC.DrawLine(x, y + 1, x + 1, y + 2);
                    }
                    else if (sum == 2 || sum == 13)
                    {
                        memDC.DrawLine(x + 1, y + 2, x + 2, y + 1);
                    }
                    else if (sum == 3 || sum == 12)
                    {
                        memDC.DrawLine(x, y + 1, x + 2, y + 1);
                    }
                    else if (sum == 4 || sum == 11)
                    {
                        memDC.DrawLine(x + 1, y, x + 2, y + 1);
                    }
                    else if (sum == 5)
                    {
                        memDC.DrawLine(x, y + 1, x + 1, y);
                        memDC.DrawLine(x + 1, y + 2, x + 2, y + 1);
                    }
                    else if (sum == 6 || sum == 9)
                    {
                        memDC.DrawLine(x + 1, y, x + 1, y + 2);
                    }
                    else if (sum == 7 || sum == 8)
                    {
                        memDC.DrawLine(x, y + 1, x + 1, y);
                    }
                    else if (sum == 10)
                    {
                        memDC.DrawLine(x, y + 1, x + 1, y + 2);
                        memDC.DrawLine(x + 1, y, x + 2, y + 1);
                    }
                }
            }
        }
    }

    if (ShowPoints)
    {
        memDC.SetPen(*wxBLACK_PEN);
        memDC.SetBrush(*wxTRANSPARENT_BRUSH);
        for (int i = 0; i < N; i++)
        {
            float x = (d[i][0] + 2.5) / 5.0 * 500;
            float y = (2.5 - d[i][1]) / 5.0 * 500;
            memDC.DrawLine(x - 5, y, x + 5, y);
            memDC.DrawLine(x, y - 5, x, y + 5);
        }
    }
}

float shepard(float i, float j, float d[100][3], int N)
{
    i = i / 100.0 - 2.5;
    j = j / 100.0 + 2.5;
    float l = 0;
    float m = 0;
    for (int k = 0; k < N; k++)
    {
        float w = 1.0 / ((i - d[k][0]) * (i - d[k][0]) + (j - d[k][1]) * (j - d[k][1]));
        l += w * d[k][2];
        m += w;
    }

    return l / m;
}