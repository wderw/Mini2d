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
    void processEvent(sf::Event& event);
    void resetView();
    float getCurrentZoomPercentage() const;

private:
    void onResize(sf::Event& event);
    void onScroll(sf::Event& event, float zoomMultiplier);
    void zoomViewAt(sf::Vector2i pixel, float zoom);

    float currentZoomPercentage{100.0f};
    sf::RenderTarget& window;
    Config& config;
};
}
