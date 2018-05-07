#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string stateID();

private:

	bool checkCollision(SDLGameObject*, SDLGameObject*);

	static const std::string _playID;
};
