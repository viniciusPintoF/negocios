#pragma once
#include <stack>
#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void pushState(GameState*);
	void changeState(GameState*);
	void popState();

	void update();
	void render();

private:
	std::stack<GameState*> _gameStates;
};
