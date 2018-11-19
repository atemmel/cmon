#pragma once
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedSprite : public sf::Drawable
{
public:
	AnimatedSprite(sf::Texture & texture);

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
