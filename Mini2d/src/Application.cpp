#include "Application.h"
#include "Logger.h"
#include <random>

namespace mini2d
{
Application::Application()
{
    settings.antialiasingLevel = 0;

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Mini 2d engine", sf::Style::Default, settings);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(300);
}

void Application::initialize()
{
    Logger::Initialize();
    ImGui::SFML::Init(*window);
    LOG_INFO("ImGui is ON.");

    srand(time(0)); LOG_WARN("Seed not set!");
    //const int seed = 1234; srand(seed); LOG_INFO("Seed is: {}", seed);
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
        default: { break; }
        }
    }
}

void Application::updateGui()
{
    static int clickCount;
    static float translation = 0;

    ImGui::SFML::Update(*window, deltaClock.restart());
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::Button("Look at this pretty button2");
    ImGui::End();

    ImGui::Begin("Development");
    ImGui::SliderFloat2("position", &translation, -1.0f, 1.0f);
    static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    ImGui::ColorEdit3("Background", color);
    ImGui::End();
}

void Application::render()
{
    window->clear(sf::Color(25,25,25,255));

    window->draw(shape);
    ImGui::SFML::Render(*window);

    window->display();
}
}
