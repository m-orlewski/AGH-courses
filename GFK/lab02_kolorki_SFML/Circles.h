#pragma once

#include "ColorCircle.h"

class Rgb : public ColorCircle
{
private:
	void convert(float* ARS, float* RGB) override
	{
		RGB[0] = ARS[1] * 255; // R changes with radius
		RGB[1] = ARS[0] * 255; // G changes with angle
		RGB[2] = ARS[2] * 255; // B changes with slider
	}

public:
	Rgb(float x, float y) : ColorCircle(x, y)
	{
		createTexture();
	}

	void prepare_to_draw(sf::RenderTarget & target, sf::RenderStates states)
	{
		for (int x = -120; x < 120; x++)
		{
			for (int y = -120; y < 120; y++)
			{
				if (x * x + y * y <= 14400)
				{
					pixels[4 * ((y + 120) * 240 + 120 - x) + 2] = static_cast<sf::Uint8>(slider_level * 255.0f);
				}
			}
		}
		texture->update(pixels);
		draw(target, states);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		ColorCircle::draw(target, states);
	}
};

class Hsl : public ColorCircle
{
private:
	float Hue_2_RGB(float v1, float v2, float vH)
	{
		if (vH < 0)
			vH++;
		if (vH > 1)
			vH--;
		if (6 * vH < 1)
			return (v1 + (v2 - v1) * 6 * vH);
		if (2 * vH < 1)
			return v2;
		if (3 * vH < 2)
			return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

		return v1;
	}

	void convert(float* HSL, float* RGB) override
	{
		if (HSL[1] == 0)
		{
			RGB[0] = RGB[1] = RGB[2] = HSL[2] * 255;
		}
		else
		{
			float var_1, var_2;
			if (HSL[2] < 0.5)
			{
				var_2 = HSL[2] * (1 + HSL[1]);
			}
			else
			{
				var_2 = (HSL[2] + HSL[1]) - (HSL[1] * HSL[2]);
			}

			var_1 = 2 * HSL[2] - var_2;

			RGB[0] = 255 * Hue_2_RGB(var_1, var_2, HSL[0] + (1.0f / 3));
			RGB[1] = 255 * Hue_2_RGB(var_1, var_2, HSL[0]);
			RGB[2] = 255 * Hue_2_RGB(var_1, var_2, HSL[0] - (1.0f / 3));
		}
	}

public:

	Hsl(float x, float y) : ColorCircle(x, y)
	{
		createTexture();
	}

	void prepare_to_draw(sf::RenderTarget& target, sf::RenderStates states)
	{

	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		ColorCircle::draw(target, states);
	}
};

class Cmy : public ColorCircle
{
private:
	void convert(float* MCY, float* RGB) override
	{
		RGB[0] = (1 - MCY[1]) * 255;
		RGB[1] = (1 - MCY[0]) * 255;
		RGB[2] = (1 - MCY[2]) * 255;
	}

public:

	Cmy(float x, float y) : ColorCircle(x, y)
	{
		createTexture();
	}

	void prepare_to_draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		for (int x = -120; x < 120; x++)
		{
			for (int y = -120; y < 120; y++)
			{
				if (x * x + y * y <= 14400)
				{
					pixels[4 * ((y + 120) * 240 + 120 - x) + 2] = static_cast<sf::Uint8>((1.0f - slider_level) * 255.0f);
				}
			}
		}
		texture->update(pixels);
		draw(target, states);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		ColorCircle::draw(target, states);
	}
};

class Hsv : public ColorCircle
{
private:
	void convert(float* HSV, float* RGB)
	{
		if (HSV[1] == 0)
		{
			RGB[0] = HSV[2] * 255;
			RGB[1] = HSV[2] * 255;
			RGB[2] = HSV[2] * 255;
		}
		else
		{
			float var_h = HSV[0] * 6;
			if (var_h == 6)
				var_h = 0;
			int var_i = static_cast<int>(var_h);
			float var_1 = HSV[2] * (1 - HSV[1]);
			float var_2 = HSV[2] * (1 - HSV[1] * (var_h - var_i));
			float var_3 = HSV[2] * (1 - HSV[1] * (1 - (var_h - var_i)));

			float var_r, var_g, var_b;
			switch (var_i)
			{
			case 0:
				RGB[0] = HSV[2] * 255;
				RGB[1] = var_3 * 255;
				RGB[2] = var_1 * 255;
				break;
			case 1:
				RGB[0] = var_2 * 255;
				RGB[1] = HSV[2] * 255;
				RGB[2] = var_1 * 255;
				break;
			case 2:
				RGB[0] = var_1 * 255;
				RGB[1] = HSV[2] * 255;
				RGB[2] = var_3 * 255;
				break;
			case 3:
				RGB[0] = var_1 * 255;
				RGB[1] = var_2 * 255;
				RGB[2] = HSV[2] * 255;
				break;
			case 4:
				RGB[0] = var_3 * 255;
				RGB[1] = var_1 * 255;
				RGB[2] = HSV[2] * 255;
				break;
			default:
				RGB[0] = HSV[2] * 255;
				RGB[1] = var_1 * 255;
				RGB[2] = var_2 * 255;
				break;
			}
		}
	}

public:

	void prepare_to_draw(sf::RenderTarget& target, sf::RenderStates states)
	{

	}

	Hsv(float x, float y) : ColorCircle(x, y)
	{
		createTexture();
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		ColorCircle::draw(target, states);
	}
};
