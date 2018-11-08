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

constexpr bool queryOk(tinyxml2::XMLError code)
{
	return code == tinyxml2::XML_SUCCESS;
}

//Todo: Abstract this mess into separate files

struct BitmapFontData
{
	struct CharData;

	BitmapFontData(const std::string & imageStr, const std::string & metaStr)
	{
		m_texture.loadFromFile(imageStr);
		m_chars = loadCharDataFromFile(metaStr);
		
		//TODO: Sort vector for easy access
	}

	std::vector<CharData> m_chars;
	sf::Texture m_texture;

private:
	struct CharData
	{
		sf::Vector2i offset,
			dimension,
			position;

		int advance = 0;
		char c = 0;
	};

	bool parseChar(tinyxml2::XMLElement* element, CharData & data)
	{
		auto pOffsetX = element->FindAttribute("offset_x"),
			pOffsetY = element->FindAttribute("offset_y"),
			pAdvance = element->FindAttribute("advance"),	//Space between this letter and the next 
			pRectW = element->FindAttribute("rect_w"),	//Width of area to draw
			pRectX = element->FindAttribute("rect_x"),	//x of area to draw
			pRectY = element->FindAttribute("rect_y"),	//y of area to draw
			pRectH = element->FindAttribute("rect_h"),	//Height of area to draw
			pChar = element->FindAttribute("id");	//character

		if(!(pOffsetX && pOffsetY && pAdvance && pRectW && pRectX && pRectY
			&& pRectH && pChar))
		{
			std::cerr << "Could not find attribute\n";
			return 0;
		}

		bool ok = queryOk(pOffsetX->QueryIntValue(&data.offset.x))
			&& queryOk(pOffsetY->QueryIntValue(&data.offset.y))
			&& queryOk(pAdvance->QueryIntValue(&data.advance))
			&& queryOk(pRectW->QueryIntValue(&data.dimension.x))
			&& queryOk(pRectX->QueryIntValue(&data.position.x))
			&& queryOk(pRectY->QueryIntValue(&data.position.y))
			&& queryOk(pRectH->QueryIntValue(&data.dimension.y))
			&& pChar->Value();

		if(!ok)
		{
			std::cerr << "Attribute has incorrect value\n";
			return 0;
		}

		data.c = *(pChar->Value());

		return 1;
	}

	std::vector<CharData> loadCharDataFromFile(const std::string & str)
	{
		std::vector<CharData> characters;

		tinyxml2::XMLDocument doc;
		auto err = doc.LoadFile(str.c_str());

		if(err != tinyxml2::XML_SUCCESS)
		{
			std::cerr << "XML ERROR: Could not open file: " << str << '\n';
			return characters;
		}

		tinyxml2::XMLElement* root = doc.FirstChildElement("font");
		if(!root) return characters;

		tinyxml2::XMLElement* child = root->FirstChildElement("chars")->FirstChildElement("char");
		CharData data;

		while(child)
		{
			if(!parseChar(child, data)) return characters;

			characters.push_back(data);
			child = child->NextSiblingElement();
		}

		return characters;
	}
};

struct BitmapText
{
	BitmapText(BitmapFontData & bmf)
		: m_bmfd(bmf)
	{
		m_sprite.setTexture(m_bmfd.m_texture);
	}

	void setPosition(sf::Vector2f pos)
	{
		m_position = pos;
	}

	void setString(const std::string && str)
	{
		m_str = str;
		m_letters.clear();

		float prevX = 0.f;
		int prevAdvance = 0;

		for(auto c : m_str)
		{
			Letter let;

			size_t index = 0, size = m_bmfd.m_chars.size();
			for(; index < size; index++)	//TODO: std find?
			{
				if(c == m_bmfd.m_chars[index].c) break;
			}

			if(index >= size) continue; //Bad character

			auto & theChar = m_bmfd.m_chars[index];

			let.dimension = sf::IntRect(theChar.position, theChar.dimension);
			let.position = sf::Vector2f((float)(prevAdvance)+prevX + theChar.offset.x, -theChar.offset.y);
			
			m_letters.push_back(let);
			prevAdvance = theChar.advance;
			prevX = let.position.x;
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
	struct Letter
	{
		char c;
		sf::Vector2f position;
		sf::IntRect dimension;
	};

	sf::Vector2f m_position;
	std::vector<Letter> m_letters;
	std::string m_str;
	BitmapFontData & m_bmfd;
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

	p1Name.setFont(titleFont);
	p2Name.setFont(titleFont);
	initPkmnNameText(p1Name);
	initPkmnNameText(p2Name);
	p1Name.setString("TEXT GOES HERE");
	p1Name.setPosition({32, -2});
	p2Name.setString("AMPHAROS");
	p2Name.setPosition({532, 498});
	
	BitmapFontData bmfd(Resources + FontTitle, Resources + "fonts/pkmndp.xml");
	BitmapText text(bmfd);

	text.setString("AMPHAROS");
	text.setPosition(sf::Vector2f(10, 300));
	

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