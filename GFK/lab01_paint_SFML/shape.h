#pragma once

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

extern sf::Texture texture;

class Shape
{
private:
	sf::Color draw_color = sf::Color::White;
	sf::Color bg_color = sf::Color::Black;
	sf::Vector2f A{0, 0};
	sf::Vector2f B{0, 0};
	char mode='\0';
public:
	Shape(sf::Color draw, sf::Color bg, sf::Vector2f a, sf::Vector2f b, char m) : draw_color(draw), bg_color(bg), A(a), B(b), mode(m) {}
	void draw(sf::RenderTarget& target, sf::RenderTexture& texture, bool save)
	{
		sf::VertexArray line(sf::LinesStrip, 2);
		sf::CircleShape circle;
		sf::RectangleShape rect;
		switch (mode)
		{
			case 'l':
				line[0].position = A;     
				line[0].color = draw_color;
				line[1].position = B;
				line[1].color = draw_color;
				target.draw(line);
				if (save)
					texture.draw(line);
				break;
			case 'c':
				circle.setRadius(sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)));
				circle.setOutlineColor(draw_color);
				circle.setFillColor(sf::Color::Transparent);
				circle.setOutlineThickness(1.0f);
				circle.setPosition(A);
				target.draw(circle);
				if (save)
					texture.draw(circle);
				break;
			case 'r':
				rect.setSize(sf::Vector2f(B.x - A.x, B.y - A.y));
				rect.setFillColor(sf::Color::Transparent);
				rect.setOutlineColor(draw_color);
				rect.setOutlineThickness(1.0f);
				rect.setPosition(A);
				target.draw(rect);
				if (save)
					texture.draw(rect);
				break;
			case 'a':
				rect.setSize(sf::Vector2f(B.x - A.x, B.y - A.y));
				rect.setFillColor(bg_color);
				rect.setOutlineColor(draw_color);
				rect.setOutlineThickness(1.0f);
				rect.setPosition(A);
				target.draw(rect);
				if (save)
					texture.draw(rect);
				break;
		}
	}
	void update_end_point(sf::Vector2f p)
	{
		B.x = p.x;
		B.y = p.y;
	}
};
