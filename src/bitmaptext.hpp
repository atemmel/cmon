#pragma once
#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include "bitmapfont.hpp"
#include "element.hpp"
#include "resource.hpp"

//Class used for drawing text in a bitmap fashion
class BitmapText : public Element
{
public:
	BitmapText(Texture & texture, BitmapFont & bmf);

	//Note: The origin of the text is its bottom-left corner
	void setPosition(sf::Vector2f pos);	
	void setScale(float scale);
	void setColor(sf::Color color);
	void setString(const std::string & str);

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	BitmapFont & m_bmf;
	Texture & m_texture;
	sf::Vector2f m_position;
	sf::Color m_color = sf::Color::White;
	std::vector<sf::Sprite> m_letters;
	std::string m_str;
	float m_scale = 1.f;
};

#endif
