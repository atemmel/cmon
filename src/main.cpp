#include "bitmaptext.hpp"
#include "resources.hpp"
#include "element.hpp"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <vector>
#include <algorithm>

class HealthBar : public sf::Drawable
{
public:
	HealthBar(sf::Vector2f dimension)
		:  m_maxWidth(dimension.x)
	{
		sf::Vector2f size = {dimension.x, dimension.y / 2.f};

		m_upperBar.setSize(size);
		m_lowerBar.setSize(size);
		m_upperBar.setFillColor(Upper::High);
		m_lowerBar.setFillColor(Lower::High);
		m_lowerBar.setPosition(0.f, size.y);
	}

	void setHealth(float health)	//Expects a value from 0 to 1
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

	void setPosition(sf::Vector2f position)
	{
		m_upperBar.setPosition(position);
		m_lowerBar.setPosition(position + sf::Vector2f(0.f, m_upperBar.getSize().y));
	}

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

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_lowerBar);
		target.draw(m_upperBar);
	}

	float m_maxWidth;
	sf::RectangleShape m_upperBar;
	sf::RectangleShape m_lowerBar;
};

const sf::Color HealthBar::Upper::High		= sf::Color(96, 248, 96);
const sf::Color HealthBar::Upper::Medium	= sf::Color(248, 168, 0);
const sf::Color HealthBar::Upper::Low		= sf::Color(248, 64, 112); //Cozy

const sf::Color HealthBar::Lower::High		= sf::Color(24, 192, 32);
const sf::Color HealthBar::Lower::Medium	= sf::Color(160, 128, 40);
const sf::Color HealthBar::Lower::Low		= sf::Color(160, 72, 88);

class BattleBox
{
public:

private:
	BitmapText m_name;
};

const static sf::VideoMode DefaultMode(1024, 768);

static bool fullscreen = 0;

int main()
{
	sf::Texture texturePlayerBox, textureEnemyBox, textureBackground, textureMessageBox;
	sf::Sprite p1Frame, p2Frame, background, messageBox;
	BitmapFont bmf(Resources::Fonts::Message, Resources::Fonts::MessageData);
	BitmapText p1Name(bmf), p2Name(bmf), upperText(bmf), lowerText(bmf);
	HealthBar p1Bar(sf::Vector2f(154.f, 6.7f)), p2Bar(sf::Vector2f(153.5f, 7.f));

	texturePlayerBox.loadFromFile(Resources::Textures::BattleUiPlayerBox);
	textureEnemyBox.loadFromFile(Resources::Textures::BattleUiEnemyBox);
	textureBackground.loadFromFile(Resources::Textures::Background);
	textureMessageBox.loadFromFile(Resources::Textures::MessageBox);
	p1Frame.setTexture(texturePlayerBox, true);
	p1Frame.setScale(1.6f, 1.6f);
	p2Frame.setTexture(textureEnemyBox, true);
	p2Frame.setScale(1.6f, 1.6f);
	background.setTexture(textureBackground);
	messageBox.setTexture(textureMessageBox);
	messageBox.setPosition(0.f, 634.f);
	messageBox.setScale(1.6f, 1.6f);

	p1Name.setScale(1.6f);
	p1Name.setString("ALTARIA");
	p1Name.setPosition(sf::Vector2f(690.f, 532.f));
	p1Bar.setPosition(sf::Vector2f(819.f, 538.f));
	
	p2Name.setScale(1.6f);
	p2Name.setString("AMPHAROS");
	p2Name.setPosition(sf::Vector2f(60.f, 72.f));
	p2Bar.setPosition(sf::Vector2f(141.f, 78.f));

	upperText.setScale(1.6f);
	upperText.setString("This is the upper text!");
	upperText.setPosition(sf::Vector2f(10.f, 688.f));

	lowerText.setScale(1.6f);
	lowerText.setString("Is this the lower text?");
	lowerText.setPosition(sf::Vector2f(10.f, 738.f));

	sf::RenderWindow window(DefaultMode, "");
	window.setFramerateLimit(60u);

	p1Frame.setPosition(640.f, 500.f);
	p2Frame.setPosition(0.f, 40.f);

	sf::View fontView = window.getView();
	fontView.setSize(static_cast<sf::Vector2f>(textureBackground.getSize()));
	sf::Vector2f center = static_cast<sf::Vector2f>(textureBackground.getSize() / 2u);
	fontView.setCenter(center);

	float health = 1.f;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) window.close();
			else if(event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Key::F8)
				window.close();

			else if(event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Enter
				&& event.key.alt)
			{
				uint32_t style = 0;
				sf::VideoMode mode;

				if(fullscreen)
				{
					style = sf::Style::Default;
					mode = DefaultMode;
				}
				else
				{
					style = sf::Style::None;
					mode = sf::VideoMode::getDesktopMode();
				}

				window.close();
				window.create(mode, "", style);
				window.setFramerateLimit(60);
		
				fullscreen ^= 1;	//Toggle

				if(fullscreen) window.setMouseCursorVisible(false);
			}

			else if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Key::H)
				{
					health -= 0.01f;
					p1Bar.setHealth(health);
				}
			}
		}

		window.setView(fontView);
		window.clear();
		window.draw(background);
		window.draw(p1Frame);
		window.draw(p2Frame);

		window.draw(p1Bar);
		window.draw(p2Bar);

		window.draw(messageBox);
		window.draw(upperText);
		window.draw(lowerText);

		window.draw(p1Name);
		window.draw(p2Name);

		window.display();
	}
	return 0;
}