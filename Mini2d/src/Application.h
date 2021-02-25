#pragma once

#include <SFML/Graphics.hpp> // Graphics.hpp must be the first include!
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Windows.h>

namespace mini2d
{
class Application
{
public:
    Application();
    void run();

private:
    void processEvents();
    void updateGui();
    void render();

    std::unique_ptr<sf::RenderWindow> window;
    sf::ContextSettings settings;
    sf::Event event;
    sf::Clock deltaClock;
    sf::CircleShape shape{ 100.f };
};
}
