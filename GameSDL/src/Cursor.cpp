#include "../include/Cursor.h"

#include "../include/ErrorHandler.h"

void Cursor::handleInput()
{
	Vector2D vec = InputModule::mousePosition();
	this->_position.setX(vec.x()-1);
	this->_position.setY(vec.y()-1);
}

Cursor::Cursor() : SDLGameObject ()
{
}

void Cursor::load(const LoaderParams* parameters)
{
	SDLGameObject::load(parameters);
	
	Vector2D vec = InputModule::mousePosition();
	this->_position.setX(vec.x() - 1);
	this->_position.setY(vec.y() - 1);

}

void Cursor::draw()
{
	SDLGameObject::draw();
}

void Cursor::update()
{
	this->handleInput();
}

void Cursor::clean(){}
