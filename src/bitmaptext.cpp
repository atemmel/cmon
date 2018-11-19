#include "bitmaptext.hpp"

BitmapText::BitmapText(BitmapFont & bmf)
	: m_bmf(bmf)
{
}

void BitmapText::setPosition(sf::Vector2f pos)
{
	for(auto & let : m_letters)
	{
		let.setPosition(let.getPosition() - m_position);
	}
	m_position = pos;
	for(auto & let : m_letters)
	{
		let.setPosition(let.getPosition() + m_position);
	}
}

void BitmapText::setScale(float scale)
{
	for(auto & let : m_letters)
	{
		let.setScale(scale, scale);
	}
	m_scale = scale;
}

void BitmapText::setColor(sf::Color color)
{
	m_color = color;

	for(auto & let : m_letters)
	{
		let.setColor(m_color);
	}
}

void BitmapText::setString(const std::string & str)
{
	m_str = str;
	m_letters.clear();

	float prevX = 0.f;
	float prevAdvance = 0.f;

	for(auto c : m_str)
	{
		sf::Sprite letter;
		letter.setTexture(m_bmf.m_texture);
		letter.setScale(m_scale, m_scale);
		letter.setColor(m_color);

		size_t index = 0, size = m_bmf.m_chars.size();
		for(; index < size; index++)	//TODO: std find?
		{
			if(c == m_bmf.m_chars[index].c) break;
		}

		if(index >= size) continue; //Bad character

		auto & theChar = m_bmf.m_chars[index];

		letter.setTextureRect(sf::IntRect(theChar.position, theChar.dimension));
		letter.setPosition(sf::Vector2f(static_cast<float>(prevAdvance) + prevX
			+ static_cast<float>(theChar.offset.x), static_cast<float>(-theChar.offset.y) * m_scale));

		m_letters.push_back(letter);
		prevAdvance = theChar.advance * m_scale;
		prevX = letter.getPosition().x;
	}

	for(auto & let : m_letters)
	{
		let.move(m_position);
	}
}

void BitmapText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(auto & let : m_letters)
	{
		target.draw(let);
	}
}
