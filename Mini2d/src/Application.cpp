#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_set>
#include "Application.h"
#include "Logger.h"
#include "Config.h"
#include "Utils.h"
#include "Vector2.h"

namespace mini2d
{

void Application::initialize()
{
    Logger::Initialize();
    loadConfig("config.json");
    setupWindow();

    ImGui::SFML::Init(*window);
    LOG_INFO("ImGui initialized.");

    prepareRng();

    const int pointCount = config.get<int>("pointCount");
    LOG_INFO("pointCount: {}", pointCount);
}

void Application::performMeasurementsAndTriangulation()
{
    /* prepare vector
    std::vector<Vtx> vtxVec{};
    vtxVec.reserve(pointCount);
    for (int i = 0; i < pointCount; ++i)
    {
        double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        Vtx v{ Vector2(rand() % ((int)window->getSize().x - 120) + 60 + quake,
                      rand() % ((int)window->getSize().y - 120) + 60 + quake), i };
        vtxVec.emplace_back(v);
    }

    std::vector<Edge> edgeVec{};
    for (int i = 0; i < pointCount; ++i)
    {
        Edge e{ vtxVec[rand() % pointCount], vtxVec[rand() % pointCount] };
        edgeVec.emplace_back(e);
    }
    auto AFL = std::unordered_set<Vtx>(std::begin(vtxVec),
        std::end(vtxVec));

    auto AFL2 = std::unordered_set<Edge>(std::begin(edgeVec),
        std::end(edgeVec));
    */


    // kdtree test begins here    
    auto kdPoints = DelaunayMachine::prepareRandomKdTreePoints(config.get<int>("pointCount"));
    //auto kdPoints = delaunayMachine.prepareKdTreeTestPoints();

    delaunayMachine = std::make_unique<DelaunayMachine>(kdPoints);
    vertices = DelaunayMachine::toSfVertices(kdPoints);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);

    // do sth
    Vtx solution;
    //solution = delaunayMachine->findLinear(kdPoints, kdPoints[1]);
    solution = delaunayMachine->findClosest(kdPoints[1]);


    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

    LOG_DEBUG("solution: {}", solution.v);
    LOG_DEBUG("Elapsed us: {}", ElapsedMicroseconds.QuadPart);
    LOG_DEBUG("Elapsed ms: {}", ElapsedMicroseconds.QuadPart / 1000);
}

void Application::prepareRng()
{
    if (config.get<bool>("isRandom"))
    {
        srand(time(0)); 
        LOG_WARN("Seed not set!");
    }
    else
    {
        int seed = config.get<int>("seed");
        srand(seed);
        LOG_INFO("Seed is: {}", seed);
    }
}

void Application::setupWindow()
{
    glContextSettings.antialiasingLevel = config.get<int>("antialiasingLevel");

    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(
            config.get<int>("clientWidth"),
            config.get<int>("clientHeight")),
            "Mini 2d engine", sf::Style::Default,
            glContextSettings
        );

    window->setVerticalSyncEnabled(config.get<bool>("verticalSync"));
    window->setFramerateLimit(config.get<int>("framerateLimit"));
    window->setView(sf::View({ 0, 0, static_cast<float>(window->getSize().x),
                                    static_cast<float>(window->getSize().y) }));

    viewController = std::make_unique<ViewController>(*window, config);
    LOG_INFO("Window setup done.");
}

void Application::loadConfig(const std::string& filename)
{
    auto path = std::filesystem::current_path().string();
    LOG_DEBUG("Current program path: {}", path);
    if (std::filesystem::exists(filename))
    {
        LOG_DEBUG("Config file found.");
        loadConfigFromFile(filename);
    }
    else
    {
        LOG_ERROR("Config file not found! Make sure {} is present in your directory: {}", filename, path);
        throw std::runtime_error("Configuration file invalid!");
    }

    LOG_INFO("Config loaded.");
}

void Application::run()
{
    initialize();
    performMeasurementsAndTriangulation();

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
    LOG_INFO("Shutting down.");
    ImGui::SFML::Shutdown();
}

void Application::loadConfigFromFile(const std::string& filename)
{
    auto configJson = Utils::loadTextFile(filename);
    auto parsedJson = Utils::parseJson(configJson);
    LOG_DEBUG("Loaded config string: \n {}", configJson);

    config.set("isRandom", parsedJson["isRandom"].bool_value());
    config.set("seed", parsedJson["seed"].int_value());
    config.set("zoomMultiplier", static_cast<float>(parsedJson["zoomMultiplier"].number_value()));
    config.set("pointCount", parsedJson["pointCount"].int_value());
    config.set("framerateLimit", parsedJson["framerateLimit"].int_value());
    config.set("clientWidth", parsedJson["clientWidth"].int_value());
    config.set("clientHeight", parsedJson["clientHeight"].int_value());
    config.set("antialiasingLevel", parsedJson["antialiasingLevel"].int_value());
    config.set("verticalSync", parsedJson["verticalSync"].bool_value());
}

void Application::processEvents()
{
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        viewController->processEvent(event);

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
    ImGui::SFML::Update(*window, deltaClock.restart());

    ImGui::Begin("Viewport");

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
    ImGui::Text("pixel position (x: %d, y: %d)", pixelPos.x, pixelPos.y);
    ImGui::Text("world position (x: %f, y: %f)", worldPos.x, worldPos.y);
    if (ImGui::Button("Reset view"))
    {
        viewController->resetView();
    }

    ImGui::Text("Zoom: %f %", viewController->getCurrentZoom());

    static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    ImGui::ColorEdit3("background color", color);

    bgColor = sf::Color(color[0] * 255.f, color[1] * 255.f, color[2] * 255.f, color[3] * 255.f);

    ImGui::End();
}

void Application::render()
{
    window->clear(bgColor);

    //window->draw(shape);
    window->draw(&vertices[0], vertices.size(), sf::Points);
    ImGui::SFML::Render(*window); // Imgui must be the last rendered item!

    window->display();
}
}
