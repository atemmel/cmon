#pragma once
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cstdint>

struct Element : public sf::Drawable
{
	virtual ~Element() = default;
	uint32_t zIndex = 1;
	bool hidden = 0;
};

#endif

