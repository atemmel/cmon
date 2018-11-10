#include "element.hpp"

bool Element::operator<(const Element & rhs)
{
	return zIndex < rhs.zIndex;
}
