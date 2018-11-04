#include "engine.hpp"
#include "gamestate.hpp"

void Engine::pushState(GameState * state)
{
	m_states.push(state);
}

void Engine::popState()
{
	m_states.pop();
}

void Engine::pollEvents()
{
	m_states.top()->pollEvents(this);
}

void Engine::update(float dt)
{
	m_states.top()->update(this, dt);
}

void Engine::draw()
{
	m_states.top()->draw(this);
}
