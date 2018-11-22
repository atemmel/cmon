#include "bitmaptext.hpp"
#include "path.hpp"
#include "element.hpp"
#include "healthbar.hpp"
#include "animatedsprite.hpp"
#include "resource.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

const static sf::VideoMode DefaultMode(1024, 768);

static bool fullscreen = 0;

int main()
{
	ResourceManager manager;

	const std::string p1Path = Path::Textures::BattlerBack + "001b.png",
		p2Path = Path::Textures::BattlerFront + "094.png";

	manager.loadFromFile<Texture>(Path::Textures::BattleUiPlayerBox);
	manager.loadFromFile<Texture>(Path::Textures::BattleUiEnemyBox);
	manager.loadFromFile<Texture>(Path::Textures::Background);
	manager.loadFromFile<Texture>(Path::Textures::MessageBox);
	manager.loadFromFile<Texture>(p1Path);
	manager.loadFromFile<Texture>(p2Path);
	manager.loadFromFile<Texture>(Path::Fonts::Message);

	auto bmt = manager.access<Texture>(Path::Fonts::Message);

	sf::Sprite p1Frame, p2Frame, background, messageBox;
	//SpriteElement p1Frame(texturePlayerBox), p2Frame(textureEnemyBox) , background(textureBackground), messageBox(textureMessageBox);
	BitmapFontData bmf(Path::Fonts::MessageData);
	BitmapText p1Name(*bmt, bmf), p2Name(*bmt, bmf), upperText(*bmt, bmf), lowerText(*bmt, bmf);
	HealthBar p1Bar(sf::Vector2f(154.f, 6.7f)), p2Bar(sf::Vector2f(153.5f, 7.f));
	AnimatedSprite p1Sprite(*manager.access<Texture>(p1Path)),
		p2Sprite(*manager.access<Texture>(p2Path));


	p1Frame.setTexture(*manager.access<Texture>(Path::Textures::BattleUiPlayerBox), true);
	p1Frame.setScale(1.6f, 1.6f);
	p2Frame.setTexture(*manager.access<Texture>(Path::Textures::BattleUiEnemyBox), true);
	p2Frame.setScale(1.6f, 1.6f);
	background.setTexture(*manager.access<Texture>(Path::Textures::Background));
	messageBox.setTexture(*manager.access<Texture>(Path::Textures::MessageBox));
	messageBox.setPosition(0.f, 634.f);
	messageBox.setScale(1.6f, 1.6f);

	p1Name.setScale(1.6f);
	p1Name.setString("BULBASAUR");
	p1Name.setPosition(sf::Vector2f(690.f, 532.f));
	p1Bar.setPosition(sf::Vector2f(819.f, 538.f));
	
	p2Name.setScale(1.6f);
	p2Name.setString("GENGAR");
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

	
	p1Sprite.setScale(3.f);
	p1Sprite.setPosition(sf::Vector2f(100.f, 300.f));
	p2Sprite.setScale(3.f);
	p2Sprite.setPosition(sf::Vector2f(300.f, 100.f));
	
	sf::View view = window.getView();
	auto backgroundPtr = manager.access<Texture>(Path::Textures::Background);
	sf::Vector2f size = static_cast<sf::Vector2f>(backgroundPtr->getSize());
	view.setSize(size);
	view.setCenter(size / 2.f);

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
		
		p1Sprite.next();
		p2Sprite.next();

		window.setView(view);
		window.clear();
		window.draw(background);

		window.draw(p1Sprite);
		window.draw(p2Sprite);

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
