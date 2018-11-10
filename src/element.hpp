#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H

#include "SFML/Graphics/Sprite.hpp"

struct Element
{
	bool operator<(const Element & rhs);

	sf::Sprite sprite;
	uint32_t zIndex = 1;
	bool hidden = 0;
	bool active = 1;
};

#endif

