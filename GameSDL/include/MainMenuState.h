#pragma once
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string stateID();

private:
	
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	
	// Callback functions for menu items
	static void _menuToPlay();
	static void _exitFromMenu();

	static const std::string _menuID;
};
