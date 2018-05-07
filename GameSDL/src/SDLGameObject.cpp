#include "../include/SDLGameObject.h"

#include "../include/Game.h"

#include "../include/ErrorHandler.h"

SDLGameObject::SDLGameObject() {}

void SDLGameObject::setPosition(int x, int y)
{
	this->_position.setX(x);
	this->_position.setY(y);
}

void SDLGameObject::setVelocity(int x, int y)
{
	this->_velocity.setX(x);
	this->_velocity.setY(y);
}

void SDLGameObject::setAcceleration(int x, int y)
{
	this->_acceleration.setX(x);
	this->_acceleration.setY(y);
}

void SDLGameObject::handleInput(){}

Vector2D SDLGameObject::position()
{
	return this->_position;
}

Vector2D SDLGameObject::velocity()
{
	return this->_velocity;
}

Vector2D SDLGameObject::acceleration()
{
	return this->_acceleration;
}

int SDLGameObject::height()
{
	return this->_height;
}

int SDLGameObject::width()
{
	return this->_width;
}

float SDLGameObject::scale()
{
	return this->_scale;
}

int SDLGameObject::flip()
{
	return this->_flip;
}

void SDLGameObject::load(const LoaderParams * parameters)
{
	this->_position = Vector2D(parameters->getX(), parameters->getY());
	this->_velocity = Vector2D(0, 0);
	this->_acceleration = Vector2D(0, 0);

	this->_width = parameters->getWidth();
	this->_height = parameters->getHeight();
	this->_scale = parameters->getScale();
	this->_textureID = parameters->getTextureID();
	this->_flip = parameters->getFlip();
	this->_numFrames = parameters->getNumFrames();

	this->_currentRow = 1;
	this->_currentFrame = 0;
}

void SDLGameObject::draw()
{

	TextureManager::Instance()->drawFrame(_textureID, (int)_position.x(), (int)_position.y(), _width, _height, _currentRow, _currentFrame, Game::Instance()->getRenderer(), _scale, _flip);
}

void SDLGameObject::update()
{
	this->_velocity += this->_acceleration;
	this->_position += this->_velocity;
}

void SDLGameObject::clean()
{
	this->~SDLGameObject();
}

