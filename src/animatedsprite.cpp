#include "animatedsprite.hpp"

AnimatedSprite::AnimatedSprite(Texture & texture)
{
	m_sprite.setTexture(texture);
	auto size = static_cast<sf::Vector2i>(texture.getSize());
	m_frames = size.x / size.y;
	m_delta.x = size.x / m_frames;
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(m_delta.x, size.y)));

}

void AnimatedSprite::next()
{
	auto rect = m_sprite.getTextureRect();

	if(m_currentFrame == m_frames)
	{
		m_currentFrame = 0;
		rect.left = 0;
		rect.top = 0;
	}
	else
	{
		rect.left += m_delta.x;
		rect.top += m_delta.y;
	}

	m_sprite.setTextureRect(rect);
	++m_currentFrame;
}