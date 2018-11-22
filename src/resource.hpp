#pragma once
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

class Resource
{
public:
	virtual bool loadFromFile(const std::string & str) = 0;
};


class Texture : public Resource, public sf::Texture
{
public:
	virtual bool loadFromFile(const std::string & str)
	{
		return sf::Texture::loadFromFile(str);
	}
};
#endif
