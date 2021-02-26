#pragma once

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "Config.h"

namespace mini2d
{
class ViewController
{
public:
    ViewController(sf::RenderTarget& window, Config& config);
    void onResize(sf::Event& event);
    void zoomOnScroll(sf::Event& event, float zoomMultiplier);
    void resetView();

private:
    void zoomViewAt(sf::Vector2i pixel, float zoom);
    sf::RenderTarget& window;
    Config& config;
};
}
