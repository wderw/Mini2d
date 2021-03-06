#include <algorithm>
#include "KdTree.h"
#include "Logger.h"

namespace mini2d
{
KdTree::KdTree(const std::vector<Vtx>& input) : input{input}
{
    root = build(input, 0);
}

void KdTree::print() const
{
    LOG_DEBUG("The root: ");
    printNode(root, 0);
}

void KdTree::printNode(std::shared_ptr<KdNode> node, int depth = 0) const
{
    if (node == nullptr)
        return;

    std::string depthIndent = "    ";
    for (int i = 0; i < depth; ++i)
    {
        depthIndent += "    ";
    }

    LOG_DEBUG("{} left: ", depthIndent);
    printNode(node->left, depth + 1);

    LOG_DEBUG("{} point: {}", depthIndent, node->point.v);

    LOG_DEBUG("{} right: ", depthIndent);
    printNode(node->right, depth + 1);
}

Vtx KdTree::findClosest(const Vtx& point)
{
    return kdTreeClosestPoint(root, point, 0)->point;
}

std::shared_ptr<KdNode> KdTree::kdTreeClosestPoint(std::shared_ptr<KdNode> node, const Vtx& point, int depth = 0)
{
    if (node == nullptr)
        return nullptr;

    int axis = depth % 2;

    std::shared_ptr<KdNode> nextBranch = nullptr;
    std::shared_ptr<KdNode> oppositeBranch = nullptr;

    auto testedPointCoordinate = axis == 0 ? point.v.x : point.v.y;
    auto testedNodeCoordinate = axis == 0 ? node->point.v.x : node->point.v.y;

    if (testedPointCoordinate < testedNodeCoordinate)
    {
        nextBranch = node->left;
        oppositeBranch = node->right;
    }
    else
    {
        nextBranch = node->right;
        oppositeBranch = node->left;
    }

    auto best = closerDistance(point, kdTreeClosestPoint(nextBranch, point, depth + 1), node);

    auto distanceToSplittingPlane = axis == 0 ? (point.v.x - node->point.v.x) : (point.v.y - node->point.v.y);
    if (point.v.distanceTo(best->point.v) > abs(distanceToSplittingPlane))
    {
        best = closerDistance(point, kdTreeClosestPoint(oppositeBranch, point, depth + 1), best);
    }

    return best;
}

std::shared_ptr<KdNode> KdTree::closerDistance(const Vtx& pivot, std::shared_ptr<KdNode> p1, std::shared_ptr<KdNode> p2)
{
    if (p1 == nullptr) return p2;
    if (p2 == nullptr) return p1;

    double d1 = pivot.v.distanceTo(p1->point.v);
    double d2 = pivot.v.distanceTo(p2->point.v);

    if (d2 == 0) return p1;
    if (d1 == 0) return p2;

    if (d1 < d2)
    {
        return p1;
    }
    else
    {
        return p2;
    }
}

std::shared_ptr<KdNode> KdTree::build(std::vector<Vtx> points, int depth = 0)
{
    int n = points.size();

    if (n == 0)
        return nullptr;

    int axis = depth % 2;

    auto comparator = [axis](const Vtx& lhs, const Vtx& rhs)
    {
        return axis == 0 ? (lhs.v.x < rhs.v.x) : (lhs.v.y < rhs.v.y);
    };
    std::sort(std::begin(points), std::end(points), comparator);

    std::size_t const mid = points.size() / 2;
    std::vector<Vtx> splitLeft(points.begin(), points.begin() + mid);
    std::vector<Vtx> splitRight(points.begin() + mid + 1, points.end());

    std::shared_ptr<KdNode> kdNode = std::make_shared<KdNode>();
    kdNode->point = points[mid];
    kdNode->left = build(splitLeft, depth + 1);
    kdNode->right = build(splitRight, depth + 1);

    return kdNode;
}
}
