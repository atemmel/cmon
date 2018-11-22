#include "element.hpp"

constexpr bool operator<(const Element & lhs, const Element & rhs)
{
	return lhs.zIndex < rhs.zIndex;
}
