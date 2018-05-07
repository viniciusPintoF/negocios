#include "../include/MainMenuState.h"

#include "../include/PlayState.h"
#include "../include/Game.h"
#include "../include/MenuButton.h"
#include "../include/Cursor.h"
#include "../include/ErrorHandler.h"
#include "../include/StateParser.h"


const std::string MainMenuState::_menuID = "MENU";

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update()
{
	if (this->active) {
		for (unsigned int i = 0; i < this->_gameObjects.size(); i++)
		{
			this->_gameObjects[i]->update();
			if (!this->active) break;
		}
	}
}

void MainMenuState::render()
{
	for (unsigned int i = 0; i < this->_gameObjects.size(); i++)
	{
		this->_gameObjects[i]->draw();
		if (!this->active) break;
	}
	
}

bool MainMenuState::onEnter()
{	
	this->active = true;
	
	// Hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	// parse the state
	StateParser stateParser;
	stateParser.parseState("./xml/test.xml", this->_menuID, &this->_gameObjects, &this->_textureIDs);

	this->_callbacks.push_back(NULL); // callbackID starts from 1
	this->_callbacks.push_back(_menuToPlay);
	this->_callbacks.push_back(_exitFromMenu);

	setCallbacks(_callbacks);

	std::cout << "Entering menu state\n";

	return true;
}

bool MainMenuState::onExit()
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

	std::cout << "Exiting menu state\n";
	this->active = false;
	return true;
}

std::string MainMenuState::stateID()
{
	return MainMenuState::_menuID;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

void MainMenuState::_menuToPlay()
{
	std::cout << "Play button clicked\n";
	Game::Instance()->stateMachine()->changeState(new PlayState);
}

void MainMenuState::_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	Game::Instance()->clean();
}
