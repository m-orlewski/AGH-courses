#include <iostream>
#include <string>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "menu.h"
#include "slider.h"

int main()
{
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    unsigned int FPS = 0, frame_counter = 0;

    sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    Menu menu;

    bool slider_moving = false;

    clock.restart().asMilliseconds();
    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::White);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.x >= 700 && event.mouseButton.x <= 750 && event.mouseButton.y >= 50 && event.mouseButton.y <= 305)
                {
                    menu.slider_moved((305.0 - event.mouseButton.y) / 255);
                    slider_moving = true;
                }
            }
            else if (slider_moving && event.type == sf::Event::MouseMoved)
            {
                if (event.mouseMove.x >= 700 && event.mouseMove.x <= 750 && event.mouseMove.y >= 50 && event.mouseMove.y <= 305)
                {
                    menu.slider_moved((305.0 - event.mouseMove.y) / 255);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                slider_moving = false;
            }

        }

        window.draw(menu);
        menu.outtextxy(window, 700, 450, std::to_string(FPS));

        if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
            clock.restart();
            frame_counter = 0;
        }
        frame_counter++;


        window.display();
    }
}