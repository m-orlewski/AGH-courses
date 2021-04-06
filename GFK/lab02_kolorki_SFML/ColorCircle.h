#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define M_PI 3.14159265358979323846
const float RADIUS = 120.0f;

class ColorCircle : public sf::CircleShape
{
public:
	const int square_size = 240; //size of a square storing the pixels for 
	sf::Texture* texture = new sf::Texture;
	sf::CircleShape* shape = new sf::CircleShape(RADIUS);

	inline void draw_to_color_pixels(int x, int y, float* converted)
	{
		pixels[4 * (y * square_size + x) + 0] = static_cast<sf::Uint8>(converted[0]);
		pixels[4 * (y * square_size + x) + 1] = static_cast<sf::Uint8>(converted[1]);
		pixels[4 * (y * square_size + x) + 2] = static_cast<sf::Uint8>(converted[2]);
		pixels[4 * (y * square_size + x) + 3] = 255;
	}

	virtual void convert(float*, float*) = 0;

	virtual void prepare_to_draw(sf::RenderTarget &, sf::RenderStates) = 0;

public:
	float x, y;
	float slider_level = 0.5f;
	sf::Uint8* pixels = new sf::Uint8[230400];

	ColorCircle(float X, float Y) : x(X), y(Y)
	{
		texture->create(square_size, square_size);
		shape->setTexture(texture);
		shape->setPosition(x, y);
	}

	void createTexture(float s=0.5f)
	{
		float r, a;// radius and angle
		float to_convert[3];// 0-angle, 1-radius, 2-slider
		to_convert[2] = s;
		float after_conversion[3];// array to store conversion results
		for (int x = -120; x < 120; x++)
		{
			for (int y = -120; y < 120; y++)
			{
				r = sqrtf(x * x + y * y) / RADIUS; // [0, 1]
				a = atan2f(y, x); // [-PI, PI]
				a += M_PI; // [0, 2PI]
				a /= 2 * M_PI; // [0, 1]
				if (r <= 1)
				{
					to_convert[0] = a;
					to_convert[1] = r;
					convert(to_convert, after_conversion);
					draw_to_color_pixels(120 - x, 120 + y, after_conversion);
				}
			}
		}
		texture->update(pixels);
	}

	void update_slider(float Z)
	{
		slider_level = Z;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*shape);
	}

	~ColorCircle()
	{
		delete pixels;
		delete texture;
		delete shape;
	}
};

