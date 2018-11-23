#include "battlerbox.hpp"

const static sf::Vector2f enemyBarDim(153.5f, 7.f);
const static sf::Vector2f playerBarDim(154.f, 6.7f);

BattlerBox::BattlerBox(BattlerBox::Character character, ResourceManager & manager)
	: frame(std::make_shared<Sprite>(Sprite()))

{
}
