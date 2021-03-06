#include "Edge.h"

template<>
struct std::hash<mini2d::Edge> {
    std::size_t operator()(const mini2d::Edge& e) const
    {
        return std::hash<int>{}(e.v1.index + e.v2.index);
    }
};

bool operator==(const mini2d::Edge& lhs, const mini2d::Edge& rhs)
{
    return (lhs.v1.index == rhs.v1.index and lhs.v2.index == rhs.v2.index) or
        (lhs.v1.index == rhs.v2.index and lhs.v2.index == rhs.v1.index);
}