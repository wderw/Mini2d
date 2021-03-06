#include "Vtx.h"

template<>
struct std::hash<mini2d::Vtx> {
    std::size_t operator()(const mini2d::Vtx& v) const
    {
        return std::hash<int>{}(v.index);
    }
};

bool operator==(const mini2d::Vtx& lhs, const mini2d::Vtx& rhs)
{
    return lhs.index == rhs.index;
}
