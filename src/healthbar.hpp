#pragma once
#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "element.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class HealthBar : public Element
{
public:
	HealthBar(sf::Vector2f dimension);

	void setHealth(float health);	//Expects a value from 0 to 1

	void setPosition(sf::Vector2f position);

private:
	struct Upper
	{
		const static sf::Color High;
		const static sf::Color Medium;
		const static sf::Color Low;
	};

	struct Lower
	{
		const static sf::Color High;
		const static sf::Color Medium;
		const static sf::Color Low;
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	float m_maxWidth;
	sf::RectangleShape m_upperBar;
	sf::RectangleShape m_lowerBar;
};

#endif
