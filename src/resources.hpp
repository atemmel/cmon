#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

namespace Resources
{
const std::string Resources = "resources/";

namespace Textures
{
	const std::string Textures = "textures/";

	const std::string BattleUiPlayerBox = Resources + Textures + "battleui/playerBox.png";
	const std::string BattleUiEnemyBox = Resources + Textures + "battleui/enemyBox.png";
	const std::string Background = Resources + Textures + "battlebacks/battlebgField.png";
	const std::string MessageBox = Resources + Textures + "battleui/messagebox.png";
};

namespace Fonts
{
	const std::string Fonts = "fonts/";

	const std::string Message = Resources + Fonts + "pkmndp.png";
	const std::string MessageData = Resources + Fonts + "pkmndp.xml";
};

namespace Data
{

};

};

#endif
