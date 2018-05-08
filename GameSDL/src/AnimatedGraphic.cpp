#include "../include/AnimatedGraphic.h"



AnimatedGraphic::AnimatedGraphic()
{
}

AnimatedGraphic::~AnimatedGraphic()
{
}

void AnimatedGraphic::load(const LoaderParams *parameters)
{
	SDLGameObject::load(parameters);
	this->_animSpeed = parameters->getAnimSpeed();
}

void AnimatedGraphic::update()
{
	this->_currentFrame = int(((SDL_GetTicks() / (1000 / this->_animSpeed)) %	this->_numFrames));
}
