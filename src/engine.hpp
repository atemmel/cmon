#pragma once
#ifndef ENGINE_HPP

#include <stack>

#include <SFML\Graphics.hpp>

class GameState;

class Engine
{
public:
	void pushState(GameState * state);
	void popState();

	void pollEvents();
	void update(float dt);
	void draw();
	
private:
	std::stack<GameState*> m_states;
	sf::RenderWindow * m_window;
};

#endif