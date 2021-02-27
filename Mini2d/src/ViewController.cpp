#include "ViewController.h"
#include "Logger.h"

namespace mini2d
{
ViewController::ViewController(sf::RenderTarget& window, Config& config) : window{window}, config{config}
{
}

void ViewController::processEvent(sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Resized:
        {
            onResize(event);
            break;
        }
        case sf::Event::MouseWheelScrolled:
        {
            onScroll(event, config.get<float>("zoomMultiplier"));
            break;
        }
        default: { break; }
    }
}

void ViewController::onResize(sf::Event& event)
{
    LOG_DEBUG("Updating viewport to new window size [W:{}, H:{}]", event.size.width, event.size.height);
    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
    currentZoomPercentage = 100;
    window.setView(sf::View(visibleArea));
}

void ViewController::onScroll(sf::Event& event, float zoomMultiplier)
{
    if (event.mouseWheelScroll.delta > 0)
    {
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.f / zoomMultiplier));
        currentZoomPercentage *= zoomMultiplier;
    }
    else if (event.mouseWheelScroll.delta < 0)
    {
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomMultiplier);
        currentZoomPercentage *= (1.f / zoomMultiplier);
    }
}

void ViewController::zoomViewAt(sf::Vector2i pixel, float zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    sf::View view{ window.getView() };
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
    window.setView(view);
}

void ViewController::resetView()
{
    sf::FloatRect visibleArea(0.f, 0.f, window.getSize().x, window.getSize().y);
    sf::View view(visibleArea);
    view.zoom(1.0f);
    currentZoomPercentage = 100;
    window.setView(view);
    LOG_DEBUG("Viewport reset.");
}
float ViewController::getCurrentZoomPercentage() const
{
    return currentZoomPercentage;
}
}
