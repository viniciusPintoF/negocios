#include "../include/PauseState.h"

#include "../include/Game.h"
#include "../include/MainMenuState.h"
#include "../include/MenuButton.h"
#include "../include/Game.h"
#include "../include/StateParser.h"
#include "../include/ErrorHandler.h"



const std::string PauseState::_pauseID = "PAUSE";

PauseState::PauseState()
{
}

PauseState::~PauseState()
{
}

void PauseState::update()
{
	if (this->active) {

		if (InputModule::WasKeyReleased(InputModule::ESC)) _resumeToPlay();

		for (int i = 0; i < this->_gameObjects.size(); i++)
		{
			if (!this->active) break;
			this->_gameObjects[i]->update();
			
		}
	}
}

void PauseState::render()
{
	for (int i = 0; i < this->_gameObjects.size(); i++)
	{
		this->_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	this->active = true;

	StateParser stateParser;
	stateParser.parseState("./xml/test.xml", this->_pauseID, &this->_gameObjects, &this->_textureIDs);

	this->_callbacks.push_back(NULL); // callbackID starts from 1
	this->_callbacks.push_back(_pauseToMenu);
	this->_callbacks.push_back(_resumeToPlay);

	setCallbacks(_callbacks);

	std::cout << "Entering PauseState\n";
	return true;

}

bool PauseState::onExit()
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
	

	
	std::cout << "Exiting PauseState\n";

	this->active = false;
	return true;
}

std::string PauseState::stateID()
{
	return this->_pauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::_pauseToMenu()
{
	Game::Instance()->stateMachine()->changeState(new MainMenuState);
}

void PauseState::_resumeToPlay()
{
	std::cout << "Resume to play\n";
	Game::Instance()->stateMachine()->popState();
}
