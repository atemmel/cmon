#pragma once
#ifndef BATTLERBOX_HPP
#define BATTLERTBOX_HPP

#include "healthbar.hpp"
#include "bitmaptext.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"

#include <memory>

class BattlerBox
{
public:
	enum Character {
		Player, Enemy
	};

	BattlerBox(Character character, ResourceManager & manager);

	std::shared_ptr<HealthBar>	bar = nullptr;
	std::shared_ptr<Sprite>		frame = nullptr;
	std::shared_ptr<BitmapText> name = nullptr;
	std::shared_ptr<BitmapText> lv = nullptr;
	std::shared_ptr<BitmapText> hp = nullptr;
};

#endif
