#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "font.h"
#include "shape.h"

class Menu : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text* text;
    sf::RectangleShape* rectangle;

    sf::Texture* colors_texture;
    sf::Sprite* colors_sprite;
    sf::Uint8* colors_pixels;
    const unsigned int colors_size_x = 765;
    const unsigned int colors_size_y = 60;
    inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
    {
        colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
        colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
        colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
        colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
    }
    sf::RectangleShape draw_color_sqr, bg_color_sqr;
public:
    char mode = '\0';
    sf::Color bg_color = sf::Color::Black;
    sf::Color draw_color = sf::Color::Black;
    Menu()
    {
        bg_color_sqr.setPosition(767, 0);
        bg_color_sqr.setSize(sf::Vector2f(32, 30));
        bg_color_sqr.setOutlineThickness(0);
        bg_color_sqr.setFillColor(bg_color);

        draw_color_sqr.setPosition(767, 31);
        draw_color_sqr.setSize(sf::Vector2f(32, 30));
        draw_color_sqr.setOutlineThickness(0);
        draw_color_sqr.setFillColor(draw_color);

        font.loadFromMemory(font_data, font_data_size);
        text = new sf::Text;
        text->setFont(font);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::White);

        rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
        rectangle->setFillColor(sf::Color::Transparent);
        rectangle->setOutlineColor(sf::Color::White);
        rectangle->setOutlineThickness(1.0f);
        rectangle->setPosition(2, 62);

        unsigned int x, y;
        colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
        for (x = 0; x < 255; x++)
            for (y = 0; y < 30; y++)
            {
                draw_to_color_pixels(x, y, x, 255, 0);
                draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
                draw_to_color_pixels(x + 510, y, 255, 0, x);
                draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
                draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
                draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
            }

        colors_texture = new sf::Texture();
        colors_texture->create(colors_size_x, colors_size_y);
        colors_texture->update(colors_pixels);

        colors_sprite = new sf::Sprite();
        colors_sprite->setTexture(*colors_texture);
        colors_sprite->setPosition(1, 1);
    }

    void outtextxy(sf::RenderTarget& target, float x, float y, const std::string& str) const
    {
        text->setPosition(x, y);
        text->setString(str);
        target.draw(*text);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        outtextxy(target, 5, 600, "f - wybor koloru rysowania");
        outtextxy(target, 5, 615, "b - wybor koloru wypełniania");
        outtextxy(target, 5, 630, "l - rysowanie linii");

        outtextxy(target, 200, 600, "r - rysowanie prostokata");
        outtextxy(target, 200, 615, "a - rysowanie wypelnionego prostokata");
        outtextxy(target, 200, 630, "c - rysowanie okregu");

        outtextxy(target, 470, 600, "w - zapis do pliku");
        outtextxy(target, 470, 615, "o - odczyt z pliku");
        outtextxy(target, 470, 630, "esc - wyjscie");

        std::string str = "Aktualne: ";
        if (mode)
            str += mode;
        outtextxy(target, 650, 615, str);

        sf::RectangleShape draw_color_sqr, bg_color_sqr;

        draw_color_sqr.setSize(sf::Vector2f(26.0f, 26.0f));
        draw_color_sqr.setFillColor(draw_color);
        draw_color_sqr.setOutlineColor(draw_color);
        draw_color_sqr.setOutlineThickness(2.0f);
        draw_color_sqr.setPosition(sf::Vector2f(768.0f, 2.0f));
        target.draw(draw_color_sqr);

        bg_color_sqr.setSize(sf::Vector2f(26.0f, 26.0f));
        bg_color_sqr.setFillColor(bg_color);
        bg_color_sqr.setOutlineColor(bg_color);
        bg_color_sqr.setOutlineThickness(2.0f);
        bg_color_sqr.setPosition(sf::Vector2f(768.0f, 32.0f));

        target.draw(bg_color_sqr);

        target.draw(*rectangle);
        target.draw(*colors_sprite);
    }

    sf::Color get_color(unsigned int x, unsigned int y)
    {
        sf::Uint8 r = colors_pixels[4 * (y * colors_size_x + x) + 0];
        sf::Uint8 g = colors_pixels[4 * (y * colors_size_x + x) + 1];
        sf::Uint8 b = colors_pixels[4 * (y * colors_size_x + x) + 2];
        return sf::Color(r, g, b);
    }

    void set_draw_color(sf::Color color)
    {
        draw_color = color;
    }

    void set_bg_color(sf::Color color)
    {
        bg_color = color;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    Menu menu;

    sf::RenderTexture texture;
    sf::Sprite sprite;

    texture.create(800, 600);
    texture.clear();
    sprite.setTexture(texture.getTexture());

    std::vector<Shape> buffer;
    bool drawing = false;
    sf::Vector2f start, end;

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::F:
                    menu.mode = 'f';
                    break;
                case sf::Keyboard::B:
                    menu.mode = 'b';
                    break;
                case sf::Keyboard::L:
                    menu.mode = 'l';
                    break;
                case sf::Keyboard::R:
                    menu.mode = 'r';
                    break;
                case sf::Keyboard::A:
                    menu.mode = 'a';
                    break;
                case sf::Keyboard::C:
                    menu.mode = 'c';
                    break;
                case sf::Keyboard::W:
                    menu.mode = 'w';
                    std::cout << "Zapis do pliku" << std::endl;
                    break;
                case sf::Keyboard::O:
                    menu.mode = 'o';
                    std::cout << "Odczyt z pliku" << std::endl;
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (menu.mode == 'f' && event.mouseButton.x < 764 && event.mouseButton.y < 60)
                {
                    sf::Color color = menu.get_color(event.mouseButton.x, event.mouseButton.y);
                    menu.set_draw_color(color);
                }
                else if (menu.mode == 'b' && event.mouseButton.x < 764 && event.mouseButton.y < 60)
                {
                    sf::Color color = menu.get_color(event.mouseButton.x, event.mouseButton.y);
                    menu.set_bg_color(color);
                }
                else if (menu.mode == '\0' || menu.mode == 'o' || menu.mode == 'w')
                {
                    continue;
                }
                else
                {
                    drawing = true;
                    start.x = end.x = event.mouseButton.x;
                    start.y = end.y = event.mouseButton.y;
                    Shape new_object = Shape(menu.draw_color, menu.bg_color, start, end, menu.mode);
                    buffer.push_back(new_object);
                }
            }

            if (drawing)
            {
                if (event.type == sf::Event::MouseMoved) // update mouse coordinates
                {
                    if (event.mouseMove.y > 60 && event.mouseMove.y < 600)
                    {
                        end.x = event.mouseMove.x;
                        end.y = event.mouseMove.y;
                        buffer[buffer.size() - 1].update_end_point(end);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    drawing = false;
                    buffer[buffer.size() - 1].update_end_point(end);
                }
            }

        }

        window.draw(menu);
        if (drawing) //display what has been drawn so far (mouse still pressed)
        {
            buffer[buffer.size() - 1].draw(window, texture, false);
        }

        for (int i = 0; i < buffer.size(); i++)
        {
            if (drawing)
                buffer[i].draw(window, texture, false);
            else
                buffer[i].draw(window, texture, true);
        }

        if (menu.mode == 'w')
        {
            sf::Image img = sprite.getTexture()->copyToImage();
            img.flipVertically();
            img.saveToFile("image.jpg");
        }
        else if (menu.mode == 'o')
        {
        }
        window.display();

    }
    return 0;
}