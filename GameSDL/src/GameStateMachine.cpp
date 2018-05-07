#include "..\include\GameStateMachine.h"

#include "../include/ErrorHandler.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::pushState(GameState *state)
{
	this->_gameStates.push(state);
	this->_gameStates.top()->onEnter();
	std::cout << "Topo e " << _gameStates.top()->stateID() << "\n";
}

void GameStateMachine::changeState(GameState *state)
{
	while (!this->_gameStates.empty())
	{
		// std::cout << "Não ta vazia.\n";
		if (this->_gameStates.top()->stateID() == state->stateID()) {
			// std::cout << "Estado requerido já está no topo da pilha.\n";
			return;
		}
		
		this->popState();
	}
	// else std::cout << "Pilha vazia, mas vou dar push.\n";
	
	this->pushState(state);
}

void GameStateMachine::popState()
{
	if (!this->_gameStates.empty())
	{
		if (this->_gameStates.top()->onExit())
		{
			delete this->_gameStates.top();
			this->_gameStates.pop();
		}
		if(!this->_gameStates.empty())
			std::cout << "Topo e " << _gameStates.top()->stateID() << "\n";
		else
			std::cout << "Pilha vazia\n";
	}
	else
		std::cout << "Pilha vazia. Nao consigo dar pop.\n";
}

void GameStateMachine::update()
{
	if (!this->_gameStates.empty()) this->_gameStates.top()->update();
}

void GameStateMachine::render()
{
	if (!this->_gameStates.empty()) this->_gameStates.top()->render();
}
