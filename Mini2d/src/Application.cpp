#include "Application.h"
#include <Windows.h>

Application::Application() : event(std::make_unique<sf::Event>())
{
    settings = std::make_unique<sf::ContextSettings>();
    settings->antialiasingLevel = 0;

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Mini2d engine", sf::Style::Default, *settings);
    window->setVerticalSyncEnabled(true);
}

void Application::run()
{
    while (window->isOpen())
    {
        processEvents();
        render();
    }
}

void Application::processEvents()
{
    while (window->pollEvent(*event))
    {
        switch (event->type)
        {
        case sf::Event::Closed:
        {
            window->close();
            break;
        }
        default: { break; }
        }
    }
}

void Application::render()
{
    window->clear();
    //window->draw(&vertices[0], vertices.size(), sf::Lines);
    window->display();
}
