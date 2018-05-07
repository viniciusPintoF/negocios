#pragma once

#include <string>
#include <map>

#include "GameObject.h"

class BaseCreator
{
public:
	
	virtual GameObject* createGameObject() const = 0;
	BaseCreator() {}
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:

	static bool registerType(std::string typeID, BaseCreator*);
	static GameObject* create(std::string typeID);

private:

	GameObjectFactory();
	~GameObjectFactory();

	static std::map < std::string, BaseCreator* > _creators;
};

