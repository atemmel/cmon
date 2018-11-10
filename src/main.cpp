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
const std::string TextureMessageBox			= "sprites/battleui/messagebox.png";
const std::string FontTitle					= "fonts/pkmndp.png";

const sf::VideoMode DefaultMode(1024, 768);

bool fullscreen = 0;

int main()
{
	sf::Texture texturePlayerBox, textureEnemyBox, textureBackground, textureMessageBox;
	sf::Sprite p1Frame, p2Frame, background, messageBox;
	BitmapFont bmf(Resources + FontTitle, Resources + "fonts/pkmndp.xml");
	BitmapText p1Name(bmf), p2Name(bmf), upperText(bmf), lowerText(bmf);

	texturePlayerBox.loadFromFile(Resources + TextureBattleUiPlayerBox);
	textureEnemyBox.loadFromFile(Resources + TextureBattleUiEnemyBox);
	textureBackground.loadFromFile(Resources + TextureBackground);
	textureMessageBox.loadFromFile(Resources + TextureMessageBox);
	p1Frame.setTexture(texturePlayerBox, true);
	p1Frame.setScale(1.6f, 1.6f);
	p2Frame.setTexture(textureEnemyBox, true);
	p2Frame.setScale(1.6f, 1.6f);
	background.setTexture(textureBackground);
	messageBox.setTexture(textureMessageBox);
	messageBox.setPosition(0, 634);
	messageBox.setScale(1.6f, 1.6f);

	p1Name.setScale(1.6f);
	p1Name.setString("ALTARIA");
	p1Name.setPosition(sf::Vector2f(594.f, 532.f));
	
	p2Name.setScale(1.6f);
	p2Name.setString("AMPHAROS");
	p2Name.setPosition(sf::Vector2f(60.f, 72.f));

	upperText.setScale(1.6f);
	upperText.setString("This is the upper text!");
	upperText.setPosition(sf::Vector2f(10.f, 688.f));

	lowerText.setScale(1.6f);
	lowerText.setString("Is this the lower text?");
	lowerText.setPosition(sf::Vector2f(10.f, 738.f));

	sf::RenderWindow window(DefaultMode, "");
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

		//circle.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));

		window.setView(fontView);
		window.clear();
		window.draw(background);
		window.draw(p1Frame);
		window.draw(p2Frame);

		window.draw(messageBox);
		window.draw(upperText);
		window.draw(lowerText);

		window.draw(p1Name);
		window.draw(p2Name);

		window.display();
	}
	return 0;
}