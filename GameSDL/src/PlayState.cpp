#include "../include/PlayState.h"

#include "../include/Game.h"
#include "../include/PauseState.h"
#include "../include/GameOverState.h"
#include "../include/Enemy.h"
#include "../include/StateParser.h"
#include "../include/ErrorHandler.h"



const std::string PlayState::_playID = "PLAY";

PlayState::PlayState()
{
}

PlayState::~PlayState()
{
}

void PlayState::update()
{
	if (this->active) {

		if (InputModule::WasKeyReleased(InputModule::ESC)) {
			Game::Instance()->stateMachine()->pushState(new PauseState);
		}
		if (InputModule::IsMouseButtonDown(InputModule::MOUSE_RB)) {
			Game::Instance()->stateMachine()->pushState(new PauseState);
		}
		

		if (checkCollision(dynamic_cast<SDLGameObject*>(_gameObjects[1]), dynamic_cast<SDLGameObject*>(_gameObjects[2])))
		{
			Game::Instance()->stateMachine()->changeState(new GameOverState);
		}

		for (int i = 0; i < this->_gameObjects.size(); i++)
		{
			this->_gameObjects[i]->update();
			if (!this->active) break;
		}
	}
}

void PlayState::render()
{
	for (int i = 0; i < this->_gameObjects.size(); i++)
	{
		this->_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
 	//SDL_ShowCursor(SDL_ENABLE);
	this->active = true;	

	StateParser sp;
	sp.parseState("./xml/test.xml", this->_playID, &this->_gameObjects, &this->_textureIDs);

	std::cout << "Entering play state\n";
	return true;
}

bool PlayState::onExit()
{
	// Celearing objects
	for (unsigned int i = 0; i < this->_gameObjects.size(); i++)
	{
		this->_gameObjects[i]->clean();
	}
	this->_gameObjects.clear();

	// Clearing textures
	for (unsigned int i = 0; i < this->_textureIDs.size(); i++)
	{
		TextureManager::Instance()->eraseTexture(_textureIDs[i]);
	}
	this->_textureIDs.clear();


	std::cout << "Exiting play state\n";
	this->active = false;
	return true;
}

std::string PlayState::stateID()
{
	return PlayState::_playID;
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2)
{
	int leftA = p1->position().x() + 10;
	int rightA = (p1->position().x() + p1->scale()*p1->width()) - 10;
	int topA = p1->position().y() + 10;
	int bottomA = (p1->position().y() + p1->scale()*p1->height()) - 10;

	int leftB = p2->position().x() + 10;
	int rightB = (p2->position().x() + p2->scale()*p2->width()) - 10;
	int topB = p2->position().y() + 10;
	int bottomB = (p2->position().y() + p2->scale()*p2->height()) - 10;

	// If any of the sides from A are outside of B
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;
	return true;
}
