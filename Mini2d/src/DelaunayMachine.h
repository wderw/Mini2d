#pragma once

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include "Vector2.h"


namespace mini2d
{

class DelaunayMachine
{
public:
    static std::vector<sf::Vertex> toSfVertices(std::vector<Vector2>& v);
    std::vector<Vector2> prepareKdTreeTestPoints();
    std::vector<Vector2> prepareRandomKdTreePoints(int count);
    Vector2 findLinear(std::vector<Vector2>& points, const Vector2& pivot)
    {
        double bestDist = DBL_MAX;
        double checkedDist = 0;
        Vector2 result;
        for (int i = 0; i < points.size(); ++i)
        {
            checkedDist = points[i].distanceTo(pivot);
            if (checkedDist < bestDist)
            {
                bestDist = checkedDist;
                result = points[i];
            }
        }
        return result;
    }
};
}
