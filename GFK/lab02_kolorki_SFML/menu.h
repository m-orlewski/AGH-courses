#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "font.h"
#include "ColorCircle.h"
#include "slider.h"
#include "Circles.h"

#include <memory>

class Menu : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text* text;

	std::unique_ptr<ColorCircle>rgb = std::make_unique<Rgb>(350, 350);
	std::unique_ptr<ColorCircle>hsv = std::make_unique<Hsv>(350, 50);
	std::unique_ptr<ColorCircle>hsl = std::make_unique<Hsl>(50, 50);
	std::unique_ptr<ColorCircle>cmy = std::make_unique<Cmy>(50, 350);

	sf::Uint8* sliderPixels = new sf::Uint8[50 * 255 * 4];
	sf::Texture* sliderTexture = new sf::Texture();
	Slider* slider = new Slider;

public:
	Menu()
	{
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(14);
		text->setFillColor(sf::Color::Black);
	}

	~Menu()
	{
		delete text;
		delete slider;
		delete sliderTexture;
		delete sliderPixels;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		rgb->prepare_to_draw(target, states);
		cmy->prepare_to_draw(target, states);
		hsl->createTexture(hsl->slider_level);
		hsv->createTexture(hsv->slider_level);
		target.draw(*hsl);
		target.draw(*hsv);
		target.draw(*(slider->slider));
		target.draw(*(slider->sliderPos));
		std::string str;

		outtextxy(target, 345, 345, "RGB");
		str = "B = ";
		str += std::to_string(static_cast<int>(rgb->slider_level * 255));
		outtextxy(target, 585, 585, str);
		outtextxy(target, 25, 345, "CMY");
		str = "Y = ";
		str += std::to_string(static_cast<int>(100 * cmy->slider_level));
		str += "%";
		outtextxy(target, 265, 585, str);
		outtextxy(target, 25, 25, "HSL");
		str = "L = ";
		str += std::to_string(hsl->slider_level);
		str.resize(9);
		outtextxy(target, 265, 265, str);
		outtextxy(target, 345, 25, "HSV");
		str = "V = ";
		str += std::to_string(hsv->slider_level);
		str.resize(9);
		outtextxy(target, 585, 265, str);
	}

	void slider_moved(float new_pos)
	{
		slider->update_slider(new_pos);
		rgb->update_slider(1 - new_pos);
		hsl->update_slider(1 - new_pos);
		cmy->update_slider(1 - new_pos);
		hsv->update_slider(1 - new_pos);
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, const std::string& str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}
};
