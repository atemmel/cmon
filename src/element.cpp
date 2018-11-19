#include "element.hpp"

constexpr bool Element::operator<(const Element & rhs) const
{
	return zIndex < rhs.zIndex;
}
