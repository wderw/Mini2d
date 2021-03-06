#pragma once

#include <vector>
#include <memory>
#include "Vtx.h"

namespace mini2d
{
struct KdNode
{
    Vtx point;
    std::shared_ptr<KdNode> left;
    std::shared_ptr<KdNode> right;
};

class KdTree
{
public:
    KdTree(const std::vector<Vtx>& input);
    void print() const;
    Vtx findClosest(const Vtx& point);


private:
    std::shared_ptr<KdNode> kdTreeClosestPoint(std::shared_ptr<KdNode>, const Vtx&, int);
    std::shared_ptr<KdNode> closerDistance(const Vtx& pivot, std::shared_ptr<KdNode> p1, std::shared_ptr<KdNode> p2);
    void printNode(std::shared_ptr<KdNode>, int) const;
    std::shared_ptr<KdNode> build(std::vector<Vtx>, int);

    const std::vector<Vtx>& input;
    std::shared_ptr<KdNode> root{nullptr};
};
}
