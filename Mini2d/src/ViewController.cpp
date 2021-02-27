#include "ViewController.h"
#include "Logger.h"

namespace mini2d
{
ViewController::ViewController(sf::RenderTarget& window, Config& config)
:
    window{window},
    config{config}
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
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                startDrag();
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                stopDrag();
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            if (isDragging())
            {
                moveView((lastX - event.mouseMove.x) / getCurrentZoom(),
                         (lastY - event.mouseMove.y) / getCurrentZoom());
            }
            saveLast(event.mouseMove.x, event.mouseMove.y);
            break;
        }
        default: { break; }
    }
}

void ViewController::onResize(sf::Event& event)
{
    LOG_DEBUG("Updating viewport to new window size [W:{}, H:{}]",
        event.size.width,
        event.size.height);

    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
    sf::View view(visibleArea);
    resetZoom(view);
    window.setView(view);
}

void ViewController::onScroll(sf::Event& event, float zoomMultiplier)
{
    if (event.mouseWheelScroll.delta > 0)
    {
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.f / zoomMultiplier));
        currentZoom *= zoomMultiplier;
    }
    else if (event.mouseWheelScroll.delta < 0)
    {
        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomMultiplier);
        currentZoom *= (1.f / zoomMultiplier);
    }
}

void ViewController::startDrag()
{
    drag = true;
}

void ViewController::stopDrag()
{
    drag = false;
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

void ViewController::moveView(float x, float y)
{
    sf::View view = window.getView();
    view.move(x, y);
    window.setView(view);
}

void ViewController::saveLast(float lastX, float lastY)
{
    this->lastX = lastX;
    this->lastY = lastY;
}

void ViewController::resetZoom(sf::View& view)
{
    view.zoom(1.0f);
    currentZoom = 1.0f;
}

bool ViewController::isDragging() const
{
    return drag;
}

void ViewController::resetView()
{
    sf::FloatRect visibleArea(0.f, 0.f, window.getSize().x, window.getSize().y);
    sf::View view(visibleArea);
    resetZoom(view);
    window.setView(view);
    LOG_DEBUG("Viewport reset.");
}
float ViewController::getCurrentZoom() const
{
    return currentZoom;
}
}
