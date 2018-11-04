#pragma once
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "engine.hpp"

class GameState
{
public:
	virtual void pollEvents(Engine * engine) = 0;
	virtual void update(Engine * engine, float dt) = 0;
	virtual void draw(Engine * engine) = 0;
protected: 
};

#endif
