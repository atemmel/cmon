#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

const std::string Resources					= "resources/";
const std::string TextureBattleUiPlayerBox	= "sprites/battleui/playerBox.png";
const std::string TextureBattleUiEnemyBox	= "sprites/battleui/enemyBox.png";
const std::string TextureBackground			= "sprites/battlebacks/battlebgField.png";
//const std::string FontTitle					= "fonts/pkmnemn.ttf";
const std::string FontTitle					= "fonts/pkmndp.png";

sf::IntRect getIntRectFromChar(char c)
{
	constexpr static int32_t BangPadding = 2;
	constexpr static int32_t LowerSymPadding = 6;

	sf::IntRect rect;

	rect.height = 20;
	rect.width = 6;
	rect.left = 2;

	if(c == '!')
	{
		rect.width = BangPadding;
		return rect;
	}
	else rect.left += BangPadding;

	if(c >= '"' && c <= '+')
	{
		rect.left += BangPadding;
		rect.left += LowerSymPadding * (c - '"');
	}

	if(c >= 'A')
	{
		rect.left += 10 * c;
	}

	return rect;
}

struct BitmapText;

struct BitmapFont 
{
	BitmapFont(const char const * str, int32_t padding, std::function<sf::IntRect(char)> fun)
		: m_padding(padding), m_fun(fun)
	{
		m_texture.loadFromFile(str);
	}

private:
	friend class BitmapText;

	std::function<sf::IntRect(char)> m_fun;
	sf::Texture m_texture;
	int32_t m_padding;
};

struct Letter
{
	char c;
	sf::Vector2f position;
	sf::IntRect dimension;
};

struct BitmapText
{
	BitmapText(BitmapFont & bmf)
		: m_bmf(bmf)
	{
		m_sprite.setTexture(m_bmf.m_texture);
	}

	void setPosition(sf::Vector2f pos)
	{
		m_position = pos;
	}

	void setString(const std::string && str)
	{
		m_str = str;
		m_letters.clear();

		for(auto c : m_str)
		{
			Letter let;
			let.c = c;
			let.dimension = m_bmf.m_fun(c);
			let.position = m_letters.empty() ? sf::Vector2f() : m_letters.back().position 
				+ sf::Vector2f(m_letters.back().dimension.width + m_bmf.m_padding, 0.f);

			m_letters.push_back(let);
		}
	}

	void draw(sf::RenderWindow & target)
	{
		for(auto & let : m_letters)
		{
			m_sprite.setPosition(m_position + let.position);
			m_sprite.setTextureRect(let.dimension);
			target.draw(m_sprite);
		}
	}
private:
	sf::Vector2f m_position;
	std::vector<Letter> m_letters;
	std::string m_str;
	BitmapFont & m_bmf;
	sf::Sprite m_sprite;
};

void initPkmnNameText(sf::Text & text)
{
	text.setCharacterSize(20u);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2u);
}

int main()
{
	
	
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

	/* This stuff broken 
	tinyxml2::XMLDocument doc;
	std::cout << "Font xml loaded: " << (doc.LoadFile("resources/fonts/pkmndp.xml") == tinyxml2::XML_SUCCESS) << '\n';

	auto chd = doc.FirstChild()->NextSibling()->LastChild();

	if(!chd) return 0;

	std::cout << chd->Value() << '\n';

	std::cin.get();

	auto ele = chd->FirstChildElement("char");

	if(!ele) return 0;

	std::cout << ele->GetText() << '\n';
	
	std::cin.get();

	*/

	p1Name.setFont(titleFont);
	p2Name.setFont(titleFont);
	initPkmnNameText(p1Name);
	initPkmnNameText(p2Name);
	p1Name.setString("TEXT GOES HERE");
	p1Name.setPosition({32, -2});
	p2Name.setString("AMPHAROS");
	p2Name.setPosition({532, 498});
	
	BitmapFont bmf((Resources + FontTitle).c_str(), 0, getIntRectFromChar);
	BitmapText text(bmf);

	text.setString("!!!\"\"\"###");
	text.setPosition(sf::Vector2f(0, 300));
	

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::None);

	window.setFramerateLimit(60);

	p1Frame.setPosition(500, 500);

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

		text.draw(window);
		//window.draw(p1Name);
		//window.draw(p2Name);
		window.display();
	}
	return 0;
}