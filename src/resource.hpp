#pragma once
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

class Resource
{
public:
	virtual void loadFromFile(const std::string & str) = 0;
};


class Texture : public sf::Texture, Resource
{
public:
	virtual void loadFromFile(const std::string & str)
	{
		sf::Texture::loadFromFile(str);
	}
};
#endif
