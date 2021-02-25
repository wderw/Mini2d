#include "Application.h"
#include "Logger.h"

namespace mini2d
{
Application::Application()
{
    settings.antialiasingLevel = 0;

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Mini 2d engine", sf::Style::Default, settings);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(300);
    window->setView(sf::View({0, 0, static_cast<float>(window->getSize().x),
                                    static_cast<float>(window->getSize().y)}));
}

void Application::initialize()
{
    Logger::Initialize();
    ImGui::SFML::Init(*window);
    LOG_INFO("ImGui initialized.");

    srand(time(0)); LOG_WARN("Seed not set!");
    //const int seed = 1234; srand(seed); LOG_INFO("Seed is: {}", seed);

    const int pointCount = 100000;
    LOG_INFO("pointCount: {}", pointCount);

    vertices.reserve(pointCount);
    for (int i = 0; i < pointCount; ++i)
    {
        double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        sf::Vertex v(sf::Vector2f(rand() % ((int)window->getSize().x - 120) + 60 + quake,
            rand() % ((int)window->getSize().y - 120) + 60 + quake), sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
        vertices.emplace_back(v);
    }
}

void Application::run()
{
    initialize();

    while (window->isOpen())
    {
        processEvents();
        updateGui();
        render();
    }

    finalize();
}

void Application::finalize()
{
    LOG_DEBUG("Shutting down.");
    ImGui::SFML::Shutdown();
}

void Application::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
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

void Application::processEvents()
{
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            window->close();
            break;
        }
        case sf::Event::Resized:
        {
            LOG_INFO("Updating the view to the new size of the window");

            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
            break;
        }
        case sf::Event::MouseWheelScrolled:
        {
            if (event.mouseWheelScroll.delta > 0)
                zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *window, (1.f / 1.1f));
            else if (event.mouseWheelScroll.delta < 0)
                zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *window, 1.1f);
            break;
        }
        default: { break; }
        }
    }
}

void Application::updateGui()
{
    static int clickCount;
    static float translation = 0;

    ImGui::SFML::Update(*window, deltaClock.restart());

    ImGui::Begin("Debug");

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
    ImGui::Text("pixel position (x: %d, y: %d)", pixelPos.x, pixelPos.y);
    ImGui::Text("world position (x: %f, y: %f)", worldPos.x, worldPos.y);

    ImGui::SliderFloat2("position", &translation, -1.0f, 1.0f);
    static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    ImGui::ColorEdit3("background color", color);

    bgColor = sf::Color(color[0] * 255.f, color[1] * 255.f, color[2] * 255.f, color[3] * 255.f);

    ImGui::End();
}

void Application::render()
{
    window->clear(bgColor);

    window->draw(shape);
    window->draw(&vertices[0], vertices.size(), sf::Points);
    ImGui::SFML::Render(*window); // Imgui must be the last rendered item!

    window->display();
}
}
