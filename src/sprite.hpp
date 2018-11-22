#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "element.hpp"
#include "resource.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Sprite : public Element
{
public:
	Sprite(Texture & texture);

	void setPosition(sf::Vector2f pos);
	void setScale(float scale);

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const;

	sf::Sprite m_sprite;
};

#endif