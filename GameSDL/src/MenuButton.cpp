#include "../include/MenuButton.h"

MenuButton::MenuButton()
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::load(const LoaderParams * parameters)
{
	SDLGameObject::load(parameters);
	this->_callbackID = parameters->getCallbackID();
	this->_currentFrame = MOUSE_OUT;
}

void MenuButton::update()
{	
	Vector2D mousePos = InputModule::mousePosition();
	if ( mousePos.x() < (this->_position.x() + (this->_width * this->_scale))	
		&& mousePos.x() > this->_position.x() 
		&& mousePos.y() < (this->_position.y() + (this->_height * this->_scale))	
		&& mousePos.y() > this->_position.y()
	   )
	{	
		// if (InputModule::IsMouseButtonDown(InputModule::MOUSE_LB) && this->_released)
		if (InputModule::IsMouseButtonDown(InputModule::MOUSE_LB))
		{
			this->_currentFrame = CLICKED;
			// this->_callback();
			this->_clicked = true;
		}

		else if (InputModule::IsMouseButtonUp(InputModule::MOUSE_LB))
		{
			this->_clicked = false;
			this->_currentFrame = MOUSE_OVER;
			this->_callback();
			
		}
		else
		{
			if(!this->_clicked) this->_currentFrame = MOUSE_OVER;
		}
	}	

	else {
		this->_clicked = false;
		this->_currentFrame = MOUSE_OUT;
	}
		
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::setCallback(void(*callback)())
{
	this->_callback = callback;
}

int MenuButton::callbackID()
{
	return this->_callbackID;
}
