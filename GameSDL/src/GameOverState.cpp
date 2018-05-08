#include "../include/GameOverState.h"

#include "../include/Game.h"
#include "../include/MainMenuState.h"
#include "../include/PlayState.h"
#include "../include/AnimatedGraphic.h"
#include "../include/MenuButton.h"
#include "../include/ErrorHandler.h"
#include "../include/StateParser.h"


const std::string  GameOverState::_gameOverID = "GAMEOVER";


GameOverState::GameOverState()
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::update()
{
	if (this->active) {
		for (unsigned int i = 0; i < this->_gameObjects.size(); i++)
		{
			this->_gameObjects[i]->update();
			if (!this->active) break;
		}
	}
}

void GameOverState::render()
{
	for (unsigned int i = 0; i < this->_gameObjects.size(); i++)
	{
		this->_gameObjects[i]->draw();
		if (!this->active) break;
	}
}

bool GameOverState::onEnter()
{
	this->active = true;

	StateParser stateParser;
	stateParser.parseState("./xml/test.xml", this->_gameOverID, &this->_gameObjects, &this->_textureIDs);

	this->_callbacks.push_back(NULL); // callbackID starts from 1
	this->_callbacks.push_back(_gameOverToMenu);
	this->_callbacks.push_back(_restartPlay);

	setCallbacks(_callbacks);

	MY_DEBUG("Entering GameOver state");
	return true;	
}

bool GameOverState::onExit()
{
	// Clearing game objects
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

	MY_DEBUG("Exiting GameOver State");
	this->active = false;
	return true;
}

std::string GameOverState::stateID()
{
	return this->_gameOverID;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for (int i = 0; i < this->_gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*> (_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*> (_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->callbackID()]);
		}

	}
}

void GameOverState::_gameOverToMenu()
{
	Game::Instance()->stateMachine()->changeState(new MainMenuState());
}

void GameOverState::_restartPlay()
{
	Game::Instance()->stateMachine()->changeState(new PlayState());
}
