#pragma once

#include "SDLGameObject.h"

class MenuButton :	public SDLGameObject
{
public:
	MenuButton();
	~MenuButton();

	virtual void load(const LoaderParams *parameters);
	virtual void update();
	virtual void clean();

	void setCallback(void(*callback)());
	int callbackID();

private:

	enum MB_ButtonState
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	bool _clicked;
	int _callbackID;
	void (*_callback) ();
};

class MenuButtonCreator : public BaseCreator
{
public:	
	GameObject * createGameObject() const { return new MenuButton(); }
};
