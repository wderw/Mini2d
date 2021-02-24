#include "Application.h"

Application::Application() : event(std::make_unique<sf::Event>())
{
    settings = std::make_unique<sf::ContextSettings>();
    settings->antialiasingLevel = 0;

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900), "Mini 2d engine", sf::Style::Default, *settings);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(300);
}

void Application::run()
{
    ImGui::SFML::Init(*window);

    while (window->isOpen())
    {
        processEvents();
        render();
    }

    ImGui::SFML::Shutdown();
}

void Application::processEvents()
{
    while (window->pollEvent(*event))
    {
        ImGui::SFML::ProcessEvent(*event);
        switch (event->type)
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

void Application::render()
{
    ImGui::SFML::Update(*window, deltaClock.restart());
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::Button("Look at this pretty button2");
    ImGui::End();

    ImGui::Begin("Development");
    float translation;
    ImGui::SliderFloat2("position", &translation, -1.0, 1.0);
    static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    ImGui::ColorEdit3("color", color);
    ImGui::End();

    window->clear();
    window->draw(shape);
    ImGui::SFML::Render(*window);
    window->display();
}
