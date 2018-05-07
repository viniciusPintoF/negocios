#pragma once
#include "GameState.h"

class MenuState : public GameState
{
public:
	MenuState(){}
	~MenuState(){}
protected:
	typedef void(*Callback)();

	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

	std::vector<Callback> _callbacks;
};

