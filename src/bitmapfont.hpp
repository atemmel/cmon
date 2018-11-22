#pragma once
#ifndef BITMAPFONT_HPP
#define BITMAPFONT_HPP

#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class BitmapFontData
{
public:
	BitmapFontData(const std::string & metaStr);
	
private:
	friend class BitmapText;

	struct CharData
	{
		sf::Vector2i offset,
			dimension,
			position;

		int advance = 0;
		char c = 0;
	};

	bool parseChar(tinyxml2::XMLElement* element, CharData & data);
	std::vector<CharData> loadCharDataFromFile(const std::string & str);

	std::vector<CharData> m_chars;
};

#endif
