#include "bitmaptext.hpp"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const std::string Resources					= "resources/";
const std::string TextureBattleUiPlayerBox	= "sprites/battleui/playerBox.png";
const std::string TextureBattleUiEnemyBox	= "sprites/battleui/enemyBox.png";
const std::string TextureBackground			= "sprites/battlebacks/battlebgField.png";
//const std::string FontTitle					= "fonts/pkmnemn.ttf";
const std::string FontTitle					= "fonts/pkmndp.png";


int main()
{
	
	
	sf::Texture texturePlayerBox, textureEnemyBox, textureBackground;
	sf::Sprite p1Frame, p2Frame, background;

	texturePlayerBox.loadFromFile(Resources + TextureBattleUiPlayerBox);
	textureEnemyBox.loadFromFile(Resources + TextureBattleUiEnemyBox);
	textureBackground.loadFromFile(Resources + TextureBackground);
	p1Frame.setTexture(texturePlayerBox, true);
	p1Frame.setScale(1.5f, 1.5f);
	p2Frame.setTexture(textureEnemyBox, true);
	p2Frame.setScale(1.5f, 1.5f);
	background.setTexture(textureBackground);

	BitmapFont bmf(Resources + FontTitle, Resources + "fonts/pkmndp.xml");
	BitmapText text(bmf);
	
	text.setScale(1.5f);
	text.setString("AMPHAROS");
	text.setPosition(sf::Vector2f(10, 300));

	uint32_t style = sf::Style::Default;

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", style);

	window.setFramerateLimit(60);

	p1Frame.setPosition(544, 500);
	p2Frame.setPosition(0, 40);

	sf::View fontView = window.getView();
	fontView.setSize(static_cast<sf::Vector2f>(textureBackground.getSize()));
	sf::Vector2f center = static_cast<sf::Vector2f>(textureBackground.getSize() / 2u);
	fontView.setCenter(center);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) window.close();
			else if(event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Key::F8)
				window.close();

			/* 
			//	This should not happen
			else if(event.type == sf::Event::Resized)
			{
				sf::Vector2f evVec{(float)event.size.width, (float)event.size.height};
				std::cout << "x: " << evVec.x << '\n' << "y: " << evVec.y << '\n';
				fontView.setSize(evVec);
			}
			*/
		}

		window.setView(fontView);
		window.clear();
		window.draw(background);
		window.draw(p1Frame);
		window.draw(p2Frame);

		window.draw(text);
		window.display();
	}
	return 0;
}