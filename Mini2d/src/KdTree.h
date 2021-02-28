#pragma once

#include <vector>
#include <memory>
#include "Vector2.h"

namespace mini2d
{
struct KdNode
{
    Vector2 point;
    std::shared_ptr<KdNode> left;
    std::shared_ptr<KdNode> right;
};

class KdTree
{
public:
    KdTree(std::vector<Vector2>& input);
    void print() const;
    Vector2 findClosest(const Vector2& point);


private:
    std::shared_ptr<KdNode> kdTreeClosestPoint(std::shared_ptr<KdNode>, const Vector2&, int);
    std::shared_ptr<KdNode> closerDistance(const Vector2& pivot, std::shared_ptr<KdNode> p1, std::shared_ptr<KdNode> p2);
    void printNode(std::shared_ptr<KdNode>, int) const;
    std::shared_ptr<KdNode> build(std::vector<Vector2>, int);

    std::vector<Vector2>& input;
    std::shared_ptr<KdNode> root{nullptr};
};
}
