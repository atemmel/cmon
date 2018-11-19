#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
#include <cstdint>

struct Element
{
	bool operator<(const Element & rhs) const;

	uint32_t zIndex = 1;
	bool hidden = 0;
};

#endif

