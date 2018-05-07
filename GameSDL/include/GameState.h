#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <vector>
#include "GameObject.h"

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string stateID() = 0;

protected:
	bool active;
	std::vector<GameObject*> _gameObjects;
	std::vector<std::string> _textureIDs;

};

#endif // !__GAME_STATE__
