#include "healthbar.hpp"

const sf::Color HealthBar::Upper::High = sf::Color(96, 248, 96);
const sf::Color HealthBar::Upper::Medium = sf::Color(248, 168, 0);
const sf::Color HealthBar::Upper::Low = sf::Color(248, 64, 112); //Cozy

const sf::Color HealthBar::Lower::High = sf::Color(24, 192, 32);
const sf::Color HealthBar::Lower::Medium = sf::Color(160, 128, 40);
const sf::Color HealthBar::Lower::Low = sf::Color(160, 72, 88);

HealthBar::HealthBar(sf::Vector2f dimension)
	: m_maxWidth(dimension.x)
{
	sf::Vector2f size = {dimension.x, dimension.y / 2.f};

	m_upperBar.setSize(size);
	m_lowerBar.setSize(size);
	m_upperBar.setFillColor(Upper::High);
	m_lowerBar.setFillColor(Lower::High);
	m_lowerBar.setPosition(0.f, size.y);
}

void HealthBar::setHealth(float health)
{
	if(health < 0.f) health = 0.f;

	if(health > 0.53f)
	{
		m_upperBar.setFillColor(Upper::High);
		m_lowerBar.setFillColor(Lower::High);
	}
	else if(health > 0.2f)
	{
		m_upperBar.setFillColor(Upper::Medium);
		m_lowerBar.setFillColor(Lower::Medium);
	}
	else
	{
		m_upperBar.setFillColor(Upper::Low);
		m_lowerBar.setFillColor(Lower::Low);
	}

	float scale = m_maxWidth * health;

	m_upperBar.setSize(sf::Vector2f(scale, m_upperBar.getSize().y));
	m_lowerBar.setSize(sf::Vector2f(scale, m_lowerBar.getSize().y));
}

void HealthBar::setPosition(sf::Vector2f position)
{
	m_upperBar.setPosition(position);
	m_lowerBar.setPosition(position + sf::Vector2f(0.f, m_upperBar.getSize().y));
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_lowerBar);
	target.draw(m_upperBar);
}