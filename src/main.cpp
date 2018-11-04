#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const std::string Resources = "resources/";
const std::string TextureBattleUiPlayerBox = "sprites/battleui/playerBox.png";
const std::string TextureBattleUiEnemyBox  = "sprites/battleui/enemyBox.png";

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "");
	window.setFramerateLimit(60);
	
	sf::Texture texturePlayerBox, textureEnemyBox;
	sf::Sprite p1Frame, p2Frame;

	texturePlayerBox.loadFromFile(Resources + TextureBattleUiPlayerBox);
	textureEnemyBox.loadFromFile(Resources + TextureBattleUiEnemyBox);
	p1Frame.setTexture(texturePlayerBox, true);
	p2Frame.setTexture(textureEnemyBox, true);

	p1Frame.setPosition(500, 500);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) window.close();
		}

		window.clear();
		window.draw(p1Frame);
		window.draw(p2Frame);
		window.display();
	}
	return 0;
}