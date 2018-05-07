#pragma once

#include "SDLGameObject.h"

class AnimatedGraphic :	public SDLGameObject
{
public:
	AnimatedGraphic();
	~AnimatedGraphic();

	void load(const LoaderParams *parameters);

	void update();
private:
	int _animSpeed;

};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new AnimatedGraphic(); }
};

