#pragma once

#include "MenuState.h"

class PauseState : public MenuState
{
public:
	PauseState();
	~PauseState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string stateID();

private:
	
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	
	static void _pauseToMenu ();
	static void _resumeToPlay ();

	static const std::string _pauseID;
};
