#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "menu.h"

class Slider
{
	friend class Menu;
private:
	sf::Uint8* sliderPixels = new sf::Uint8[50 * 255 * 4];
	sf::Texture* sliderTexture = new sf::Texture();
	sf::RectangleShape* slider = new sf::RectangleShape(sf::Vector2f(50, 255));
	sf::RectangleShape* sliderPos = new sf::RectangleShape(sf::Vector2f(50, 3));

	float pos = 0.5f;

	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned int z)
	{
		sliderPixels[4 * (y * 50 + x) + 0] = z;
		sliderPixels[4 * (y * 50 + x) + 1] = z;
		sliderPixels[4 * (y * 50 + x) + 2] = z;
		sliderPixels[4 * (y * 50 + x) + 3] = 255;
	}
public:
	Slider()
	{
		for (int x = 2; x < 50; ++x)
		{
			for (int y = 1; y < 255; ++y)
			{
				draw_to_color_pixels(x, y, y);
			}
		}
		sliderTexture->create(50, 255);
		sliderTexture->update(sliderPixels);

		slider->setTexture(sliderTexture);
		slider->setPosition(700, 50);
		slider->setOutlineColor(sf::Color::Black);
		slider->setOutlineThickness(1.0f);

		sliderPos->setPosition(700, 177.5);
		sliderPos->setFillColor(sf::Color::Red);
	}

	void update_slider(float new_pos)
	{
		pos = new_pos;
		sliderPos->setPosition(700, 305 - (pos * 255));
	}

};
