#pragma once
#ifndef SPRITEELEMENT_HPP
#define SPRITEELEMENT_HPP

#include "element.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SpriteElement : public Element
{
public:
	SpriteElement(sf::Texture & texture);

	void setPosition(sf::Vector2f pos);
	void setScale(float scale);

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const;

	sf::Sprite m_sprite;
};

#endif
