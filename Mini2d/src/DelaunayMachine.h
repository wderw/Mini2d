#pragma once

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include "KdTree.h"
#include "Vtx.h"


namespace mini2d
{

class DelaunayMachine
{
public:
    DelaunayMachine(const std::vector<Vtx>& vec);
    Vtx findClosest(const Vtx& pivot);
    Vtx findLinear(const Vtx& pivot);

    // misc pointset tools:
    static std::vector<sf::Vertex> toSfVertices(std::vector<Vtx>& v);
    static std::vector<Vtx> prepareKdTreeTestPoints();
    static std::vector<Vtx> prepareRandomKdTreePoints(int count);

private:
    std::unique_ptr<KdTree> kdTree;
    const std::vector<Vtx>& input;
};
}
