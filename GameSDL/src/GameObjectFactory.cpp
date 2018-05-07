#include "..\include\GameObjectFactory.h"

#include "../include/ErrorHandler.h"

std::map < std::string, BaseCreator* > GameObjectFactory::_creators;

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator *pCreator)
{
	std::map < std::string, BaseCreator* >::iterator it = _creators.find(typeID);

	// if the type is already registered, do nothing
	if (it != _creators.end()) {
		delete pCreator;
		return false;
	}

	_creators[typeID] = pCreator;
	return true;
}

GameObject * GameObjectFactory::create(std::string typeID)
{
	std::map < std::string, BaseCreator* >::iterator it = _creators.find(typeID);
	
	if (it == _creators.end()) {
		LOG_ERROR("could not find type" << typeID);
		return NULL;
	}

	BaseCreator* pCreator = (*it).second;
	return pCreator->createGameObject();
}
