#pragma once

#include "MenuState.h"

class GameOverState : public MenuState
{
public:
	GameOverState();
	~GameOverState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string stateID();

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void _gameOverToMenu();
	static void _restartPlay();

	static const std::string _gameOverID;
};

