#ifndef _ENEMY_
#define _ENEMY_


#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Cursor : public SDLGameObject
{
protected:

	void handleInput();

public:
	Cursor();

	void load(const LoaderParams *parameters);

	void draw();

	void update();

	void clean();

};

class CursorCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new Cursor(); }	
};

#endif