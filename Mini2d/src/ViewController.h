#pragma once

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

namespace mini2d
{
class ViewController
{
public:
    ViewController(sf::RenderTarget& window);
    void onResize(sf::Event& event);
    void zoomOnScroll(sf::Event& event, float zoomMultiplier);
    void resetView();

private:
    void zoomViewAt(sf::Vector2i pixel, float zoom);
    sf::RenderTarget& window;
};
}
