#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Application
{
public:
    Application();
    void run();

private:
    void processEvents();
    void render();

    std::unique_ptr<sf::ContextSettings> settings;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::Event> event;
};
