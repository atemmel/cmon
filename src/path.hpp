#pragma once
#ifndef PATH_HPP
#define PATH_HPP

#include <string>

namespace Path
{
const std::string Resources = "resources/";

namespace Textures
{
	const std::string Textures = Resources + "textures/";
	const std::string BattlerFront	= Textures + "battlers/Front/";
	const std::string BattlerBack	= Textures + "battlers/Back/";

	const std::string BattleUiPlayerBox = Textures + "battleui/playerBox.png";
	const std::string BattleUiEnemyBox	= Textures + "battleui/enemyBox.png";
	const std::string Background = Textures + "battlebacks/battlebgField.png";
	const std::string MessageBox = Textures + "battleui/messagebox.png";
};

namespace Fonts
{
	const std::string Fonts = Resources + "fonts/";

	const std::string Message = Fonts + "pkmndp.png";
	const std::string MessageData = Fonts + "pkmndp.xml";
};

namespace Data
{

};

};

#endif
