#include "element.hpp"

bool Element::operator<(const Element & rhs) const
{
	return zIndex < rhs.zIndex;
}
