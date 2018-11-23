#pragma once
#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "resource.hpp"
#include "sprite.hpp"

#include <SFML/Graphics.hpp>

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(Texture & texture);

	void next();
private:
	sf::Vector2i m_delta;
	int m_frames;
	int m_currentFrame = 0;
};

#endif
