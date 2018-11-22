#include "sprite.hpp"

Sprite::Sprite(Texture & texture)
{
	m_sprite.setTexture(texture, true);
}

void Sprite::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Sprite::setScale(float scale)
{
	m_sprite.setScale(scale, scale);
}

void Sprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
