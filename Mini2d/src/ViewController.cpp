#include "ViewController.h"
#include "Logger.h"

namespace mini2d
{
ViewController::ViewController(sf::RenderTarget& window) : window{window}
{
}

void ViewController::onResize(sf::Event& event)
{
    LOG_INFO("Updating viewport to new window size [W:{}, H:{}]", event.size.width, event.size.height);
    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
    window.setView(sf::View(visibleArea));
}

void ViewController::zoomOnScroll(sf::Event& event, float zoomMultiplier)
{
    if (event.mouseWheelScroll.delta > 0)
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.f / zoomMultiplier));
    else if (event.mouseWheelScroll.delta < 0)
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomMultiplier);

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
    window.setView(view);
}
}
