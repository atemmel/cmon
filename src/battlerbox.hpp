#pragma once
#ifndef BATTLERBOX_HPP
#define BATTLERTBOX_HPP

#include "healthbar.hpp"
#include "bitmaptext.hpp"

#include <memory>

class BattlerBox
{
public:
	std::shared_ptr<HealthBar> bar = nullptr;
	std::shared_ptr<BitmapText> name = nullptr;
	std::shared_ptr<BitmapText> lv = nullptr;
	std::shared_ptr<BitmapText> hp = nullptr;
};

#endif
