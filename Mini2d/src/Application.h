#pragma once

#include <SFML/Graphics.hpp> // Graphics.hpp must be the first include!
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ViewController.h"
#include "DelaunayMachine.h"
#include "Config.h"

namespace mini2d
{
class Application
{
public:
    void run();
    Config config;

private:
    void initialize();
    void finalize();
    void loadConfig(const std::string& filename);
    void loadConfigFromFile(const std::string& filename);
    void prepareRng();
    void setupWindow();
    void processEvents();
    void updateGui();
    void render();

    std::unique_ptr<sf::RenderWindow> window;
    sf::ContextSettings glContextSettings;
    sf::Event event;
    sf::Clock deltaClock;
    DelaunayMachine delaunayMachine;

    std::unique_ptr<ViewController> viewController;
    sf::CircleShape shape{50.f};
    std::vector<sf::Vertex> vertices{};
    sf::Color bgColor{25, 25, 25, 255};
};
}
