#include "DelaunayMachine.h"

namespace mini2d
{
DelaunayMachine::DelaunayMachine(const std::vector<Vtx>& input) : input{input}
{
    kdTree = std::make_unique<KdTree>(input);
}

Vtx DelaunayMachine::findClosest(const Vtx& pivot)
{
    return kdTree->findClosest(pivot);
}

Vtx DelaunayMachine::findLinear(const Vtx& pivot)
{
    double bestDist = DBL_MAX;
    double checkedDist = 0;
    Vtx result;
    for (int i = 0; i < input.size(); ++i)
    {
        checkedDist = input[i].v.distanceTo(pivot.v);
        if (checkedDist < bestDist)
        {
            bestDist = checkedDist;
            result = input[i];
        }
    }
    return result;
}

std::vector<sf::Vertex> DelaunayMachine::toSfVertices(std::vector<Vtx>& vtxs)
{
    std::vector<sf::Vertex> result{};
    result.reserve(vtxs.size());
    for (const auto& vtx : vtxs)
    {
        result.emplace_back(sf::Vertex(sf::Vector2f(vtx.v.x, vtx.v.y)));
    }
    return result;
}

std::vector<Vtx> DelaunayMachine::prepareRandomKdTreePoints(int count)
{
    std::vector<Vtx> kdTreePoints{};
    kdTreePoints.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        double quake = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        Vtx v({ {rand() % (1440 - 120) + 60 + quake,
            rand() % (900 - 120) + 60 + quake}, i });
        kdTreePoints.emplace_back(v);
    }

    return kdTreePoints;
}

std::vector<Vtx> DelaunayMachine::prepareKdTreeTestPoints()
{
    std::vector<Vtx> kdTreePoints{};
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
    kdTreePoints.emplace_back(Vtx{ { 40, 70 }, 0 });
    kdTreePoints.emplace_back(Vtx{ { 70, 130 }, 1 });
    kdTreePoints.emplace_back(Vtx{ { 90, 40 },  2 });
    kdTreePoints.emplace_back(Vtx{ { 110, 100 }, 3 });
    kdTreePoints.emplace_back(Vtx{ { 140, 110 }, 4 });
    kdTreePoints.emplace_back(Vtx{ { 150, 30 }, 5 });
    kdTreePoints.emplace_back(Vtx{ { 160, 100 }, 6 });
    kdTreePoints.emplace_back(Vtx{ { 190, 150 }, 7 });

    return kdTreePoints;
}
}
