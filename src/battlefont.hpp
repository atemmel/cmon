#pragma once
#ifndef BATTLEFONT_HPP
#define BATTLEFONT_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>

class BattleFont : public sf::Drawable
{
public:
	BattleFont() = default;

	void setStr(const std::string & str);
	void setTexture(sf::Texture * texture);

	void draw(const sf::RenderTarget & target, const sf::RenderStates & states) const;

private:
	std::vector<sf::Sprite> letters;
	sf::Texture * m_texture = nullptr;
	std::string m_str;
};

#endif BATTLEFONT_HPP
