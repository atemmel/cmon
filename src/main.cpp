#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const std::string Resources					= "resources/";
const std::string TextureBattleUiPlayerBox	= "sprites/battleui/playerBox.png";
const std::string TextureBattleUiEnemyBox	= "sprites/battleui/enemyBox.png";
const std::string TextureBackground			= "sprites/battlebacks/battlebgField.png";
//const std::string FontTitle					= "fonts/pkmnemn.ttf";
const std::string FontTitle					= "fonts/pkmndp.ttf";

struct ShadowedText : public sf::Drawable
{
	void setFont(sf::Font & font)
	{
		front.setFont(font);
		back.setFont(font);
	}

	void setOffset(sf::Vector2i off)
	{
		offset = off;
	}

	void setString(const std::string & str)
	{
		front.setString(str);
		back.setString(str);
	}

	void setPosition(sf::Vector2i pos)
	{
		front.setPosition(static_cast<sf::Vector2f>(pos));
		back.setPosition(static_cast<sf::Vector2f>(pos + offset));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(back);
		target.draw(front);
	}

	sf::Text front, back;
private:
	sf::Vector2i offset;
};

void initPkmnNameText(sf::Text & text)
{
	text.setCharacterSize(20u);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2u);
}

void initPkmnNameText(ShadowedText & text)
{
	text.back.setCharacterSize(20u);
	text.front.setCharacterSize(20u);
	text.back.setFillColor(sf::Color::Black);
	text.front.setFillColor(sf::Color::White);
	text.setOffset({1, 1});
}

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::None);
	
	window.setFramerateLimit(60);
	
	sf::Texture texturePlayerBox, textureEnemyBox, textureBackground;
	sf::Font titleFont;
	sf::Sprite p1Frame, p2Frame, background;
	sf::Text p1Name, p2Name;

	texturePlayerBox.loadFromFile(Resources + TextureBattleUiPlayerBox);
	textureEnemyBox.loadFromFile(Resources + TextureBattleUiEnemyBox);
	textureBackground.loadFromFile(Resources + TextureBackground);
	titleFont.loadFromFile(Resources + FontTitle);
	p1Frame.setTexture(texturePlayerBox, true);
	p2Frame.setTexture(textureEnemyBox, true);
	background.setTexture(textureBackground);

	
	p1Name.setFont(titleFont);
	p2Name.setFont(titleFont);
	initPkmnNameText(p1Name);
	initPkmnNameText(p2Name);
	p1Name.setString("TEXT GOES HERE");
	p1Name.setPosition({32, -2});
	p2Name.setString("AMPHAROS");
	p2Name.setPosition({532, 498});
	

	p1Frame.setPosition(500, 500);

	sf::View fontView = window.getView();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) window.close();
			if(event.type == sf::Event::KeyPressed
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

		window.draw(p1Name);
		window.draw(p2Name);
		window.display();
	}
	return 0;
}