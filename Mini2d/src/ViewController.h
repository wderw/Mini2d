#pragma once

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "Config.h"
#include "Vector2.h"

namespace mini2d
{
class ViewController
{
public:
    ViewController(sf::RenderTarget& window, Config& config);
    void processEvent(sf::Event& event);
    void resetView();
    float getCurrentZoom() const;

private:
    void onResize(sf::Event& event);
    void onScroll(sf::Event& event, float zoomMultiplier);
    void startDrag();
    void stopDrag();
    void zoomViewAt(sf::Vector2i pixel, float zoom);
    void moveView(float x, float y);
    void saveLast(float lastX, float lastY);

    bool isDragging{false};
    float lastX{0};
    float lastY{0};
    float currentZoom{1.0f};
    sf::RenderTarget& window;
    Config& config;
};
}
