#pragma once
#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "resource.hpp"

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Drawable
{
public:
	AnimatedSprite(Texture & texture);

	void next();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void setPosition(sf::Vector2f pos);
	void setScale(float scale);

private:
	sf::Vector2i m_delta;
	sf::Sprite m_sprite;
	int m_frames;
	int m_currentFrame = 0;
};

#endif
