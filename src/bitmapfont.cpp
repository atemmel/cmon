#include "bitmapfont.hpp"

BitmapFont::BitmapFont(const std::string & imageStr, const std::string & metaStr)
{
	m_texture.loadFromFile(imageStr);
	m_chars = loadCharDataFromFile(metaStr);

	//TODO: Sort vector for easy access
}

bool BitmapFont::parseChar(tinyxml2::XMLElement* element, BitmapFont::CharData & data)
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

std::vector<BitmapFont::CharData> BitmapFont::loadCharDataFromFile(const std::string & str)
{
	std::vector<BitmapFont::CharData> characters;
	tinyxml2::XMLDocument doc;
	CharData data;

	if(!queryOk(doc.LoadFile(str.c_str())))
	{
		std::cerr << "XML ERROR: Could not open file: " << str << '\n';
		return characters;
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("font");
	if(!root) return characters;	//Bail
	tinyxml2::XMLElement* child = root->FirstChildElement("chars")->FirstChildElement("char");

	while(child)
	{
		if(!parseChar(child, data)) return characters;

		characters.push_back(data);
		child = child->NextSiblingElement();
	}

	return characters;
}