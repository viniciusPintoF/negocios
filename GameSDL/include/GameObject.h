#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "TextureManager.h"
#include "LoaderParams.h"

class GameObject
{
protected:

	GameObject() {}
	virtual ~GameObject(){}	

public:
	
	// 'virtual' means that when you call a function through a pointer, it uses te defition from the type of the object itself, not the type of its pointer.

	// pure virtual functions distincted by '= 0' mens that any derived classes is forced to also declare and implement the function

	virtual void load(const LoaderParams *parameters) = 0;

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual void clean() = 0;

};

#endif