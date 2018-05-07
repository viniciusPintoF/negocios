#include "../include/Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::load(const LoaderParams * parameters)
{
	SDLGameObject::load(parameters);
	this->_velocity.setY(2);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	this->_currentFrame = int(((SDL_GetTicks() / 80) % _numFrames));

	if (this->_position.y() < 0) {
		this->_velocity.setY(2);
	}
	else if (this->_position.y() > 480-(_height*_scale)) {
		this->_velocity.setY(-2);
	}

	SDLGameObject::update();
}

void Enemy::clean()
{
}

