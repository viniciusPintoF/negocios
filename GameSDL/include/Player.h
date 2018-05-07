#ifndef _PLAYER_
#define _PLAYER_

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
private:

	void handleInput();

public:
 

	Player();

	void load(const LoaderParams *parameters);

	void draw();

	void update();

	void clean();
	
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new Player(); }
};

#endif