#pragma once
#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include "bitmapfont.hpp"

class BitmapText : public sf::Drawable
{
public:
	BitmapText(BitmapFont & bmf);

	void setPosition(sf::Vector2f pos);
	void setScale(float scale);
	void setColor(sf::Color color);
	void setString(const std::string & str);

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	sf::Vector2f m_position;
	sf::Color m_color = sf::Color::White;
	float m_scale = 1.f;
	std::vector<sf::Sprite> m_letters;
	std::string m_str;
	BitmapFont & m_bmf;
};


#endif
