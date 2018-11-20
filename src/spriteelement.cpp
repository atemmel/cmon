#include "spriteelement.hpp"

SpriteElement::SpriteElement(sf::Texture & texture)
{
	m_sprite.setTexture(texture, true);
}

void SpriteElement::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void SpriteElement::setScale(float scale)
{
	m_sprite.setScale(scale, scale);
}

void SpriteElement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
