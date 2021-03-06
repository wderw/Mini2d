#include "DelaunayMachine.h"

namespace mini2d
{
std::vector<sf::Vertex> DelaunayMachine::toSfVertices(std::vector<Vector2>& v)
{
    std::vector<sf::Vertex> result{};
    result.reserve(v.size());
    for (auto vec : v)
    {
        result.emplace_back(sf::Vertex(sf::Vector2f(vec.x, vec.y)));
    }
    return result;
}

std::vector<Vector2> DelaunayMachine::prepareRandomKdTreePoints(int count)
{
    std::vector<Vector2> kdTreePoints{};
    kdTreePoints.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        Vector2 v(rand() % (1440 - 120) + 60 + quake,
            rand() % (900 - 120) + 60 + quake);
        kdTreePoints.emplace_back(v);
    }

    return kdTreePoints;
}

std::vector<Vector2> DelaunayMachine::prepareKdTreeTestPoints()
{
    std::vector<Vector2> kdTreePoints{};
    /* set 1
    kdTreePoints.emplace_back(Vector2{ 63.63961 , 144.23502 });
    kdTreePoints.emplace_back(Vector2{ 222.23357 , 385.66147 });
    kdTreePoints.emplace_back(Vector2{ 545.48236 , 146.25533 });
    kdTreePoints.emplace_back(Vector2{ 645.48749 , 502.83917 });
    kdTreePoints.emplace_back(Vector2{ 1043.4875 , 168.47868 });
    kdTreePoints.emplace_back(Vector2{ 1494.0156 , 590.72247 });
    kdTreePoints.emplace_back(Vector2{ 1096.0155 , 661.43311 });
    kdTreePoints.emplace_back(Vector2{ 803.07129 , 323.03201 });
    kdTreePoints.emplace_back(Vector2{ 358.60416 , 654.36206 });
    kdTreePoints.emplace_back(Vector2{ 510.12704 , 321.01172 });
    kdTreePoints.emplace_back(Vector2{ 852.56873 , 677.59558 });
    */

    // set 2
    kdTreePoints.emplace_back(Vector2{ 40, 70 });
    kdTreePoints.emplace_back(Vector2{ 70, 130 });
    kdTreePoints.emplace_back(Vector2{ 90, 40 });
    kdTreePoints.emplace_back(Vector2{ 110, 100 });
    kdTreePoints.emplace_back(Vector2{ 140, 110 });
    kdTreePoints.emplace_back(Vector2{ 150, 30 });
    kdTreePoints.emplace_back(Vector2{ 160, 100 });
    kdTreePoints.emplace_back(Vector2{ 190, 150 });    

    return kdTreePoints;
}
}
