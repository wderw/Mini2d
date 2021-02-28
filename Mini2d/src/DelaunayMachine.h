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
    std::vector<Vector2> prepareKdTreePoints();

};
}
