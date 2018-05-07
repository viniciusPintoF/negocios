#include "../include/Player.h"

#include "../include/Game.h"

#include "../include/ErrorHandler.h"



Player::Player()
{
	
}

void Player::load(const LoaderParams * parameters)
{
	SDLGameObject::load(parameters);
	this->_currentRow = 2;
}

void Player::handleInput()
{
	bool joyInit = InputModule::JoysticksInitialized();

	// MOVEMENT

	// Helicopter

	/*
	Vector2D offset = Vector2D((this->_width*this->_scale)/2, (this->_height*this->_scale)/2);
	Vector2D target = *InputModule::mousePosition() - offset;
	this->_velocity = target - this->_position;
	this->_velocity /= 50;
	*/

	// Joystick	
	/*
	if (joyInit)
	{
	int xValueLeft = InputModule::StickXValue(0, InputModule::LEFT_STICK);
	int yValueLeft = InputModule::StickYValue(0, InputModule::LEFT_STICK);

	if (xValueLeft > 0 || xValueLeft < 0)
	this->_velocity.setX(2 * xValueLeft);

	if (yValueLeft > 0 || yValueLeft < 0)
	this->_velocity.setY(2 * yValueLeft);
	}
	*/

	// Keyboard

	/*if (InputModule::isKeyDown(InputModule::RIGHT)) this->_velocity.setX(5);
	if (InputModule::isKeyDown(InputModule::LEFT)) this->_velocity.setX(-5);
	if (InputModule::isKeyDown(InputModule::UP)) this->_velocity.setY(-5);
	if (InputModule::isKeyDown(InputModule::DOWN)) this->_velocity.setY(5);*/

	if (InputModule::IsKeyPressed(InputModule::RIGHT)) this->_velocity.setX(this->_velocity.x() + 8);
	if (InputModule::IsKeyPressed(InputModule::LEFT)) this->_velocity.setX(this->_velocity.x() - 8);
	if (InputModule::IsKeyPressed(InputModule::UP)) this->_velocity.setY(this->_velocity.y() - 8);
	if (InputModule::IsKeyPressed(InputModule::DOWN)) this->_velocity.setY(this->_velocity.y() + 8);

	if (InputModule::WasKeyPressed(InputModule::SPACE)) std::cout << "Apertou\n";
	if (InputModule::WasKeyReleased(InputModule::SPACE)) std::cout << "Soltou\n";




	// ACTION
	// Play guitar (joystick and keyboard)
	/*if (InputModule::IsKeyPressed(SDL_SCANCODE_SPACE) || (joyInit && InputModule::JoyButtonState(0, 2)))
	{
	this->_textureID = "guitar";
	this->_velocity.setX(0);
	this->_velocity.setY(0);
	this->_currentRow = 1;
	this->_width = 103;
	this->_height = 89;
	this->_scale = 1.1;
	}*/


}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{	
	// Default state
	this->_velocity.setX(0);
	this->_velocity.setY(0);
	/*
	this->_width = 100;
	this->_height = 100;
	this->_scale = 1;
	this->_textureID = "trump";	
	*/


	// Frame if walking
	// this->_currentFrame = int(((SDL_GetTicks() / 80) % 6));
	this->_currentRow = int(((SDL_GetTicks() / 50) % 4))+1;

	// Input modifications
	this->handleInput();	

	// Frame if standing

	/*if (this->_velocity.x() == 0 && this->_velocity.y() == 0 && this->_textureID == "trump")
	{
		if (this->_currentRow == 1) this->_currentFrame = 5;
		if (this->_currentRow == 3) this->_currentFrame = 4;
		if (this->_currentRow == 2) this->_currentFrame = 1;
	}*/

	// Look direction
	
	if (this->_velocity.x() < 0)
	{
		// this->_currentRow = 2;
		this->_flip = true;	}		

	if (this->_velocity.x() > 0)
	{
		// this->_currentRow = 2;
		this->_flip = false;
	}	
	
	/*
	if (this->_velocity.y() > 0)
		this->_currentRow = 1;

	if (this->_velocity.y() < 0)
		this->_currentRow = 3;
	*/	

	if (this->_position.x() > 640) this->_position.setX(-(this->_scale*this->_width));
	if (this->_position.x() < (-(this->_scale*this->_width))) this->_position.setX(640);

	SDLGameObject::update();
		
}

void Player::clean()
{
	this->~Player();
}