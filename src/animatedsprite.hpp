#pragma once
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedSprite : public sf::Drawable
{
public:
	AnimatedSprite(sf::Texture & texture)
	{
		m_sprite.setTexture(texture);
		auto size = static_cast<sf::Vector2i>(texture.getSize());
		m_frames = size.x / size.y;
		m_delta.x = size.x / m_frames;
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(m_delta.x, size.y)));

	}

	void update()
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

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}

	void setPosition(sf::Vector2f pos)
	{
		m_sprite.setPosition(pos);
	}

	void setScale(float scale)
	{
		m_sprite.setScale(scale, scale);
	}

private:
	int calculateFrames(sf::Texture & texture)
	{
		const sf::Image img = texture.copyToImage();
		const sf::Color transparent = sf::Color::Transparent;
		const auto size = img.getSize();
		constexpr unsigned int minConsecutive = 15u;

		unsigned int consecutive = 0u;
		unsigned int n = 1u;
		
		for(unsigned int i = 0u; i < size.x; i++)
		{
			for(unsigned int j = 0u; j < size.y; j++)
			{
				const sf::Color pixel = img.getPixel(i, j);

				if(pixel == transparent)
				{
					if(j + 1 == size.y) ++consecutive;
				}
				else
				{
					consecutive = 0u;
					break;
				}
			}
			if(consecutive == minConsecutive)
			{
				++n;
			}
		}

		return n;
	}

	sf::Vector2i m_delta;
	sf::Sprite m_sprite;
	int m_frames;
	int m_currentFrame = 0;
};

#endif
