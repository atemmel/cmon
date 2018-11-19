#pragma once
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>

#include <cstdint>

struct Element : public sf::Drawable
{
	constexpr bool operator<(const Element & rhs) const;

	uint32_t zIndex = 1;
	bool hidden = 0;
};

#endif

