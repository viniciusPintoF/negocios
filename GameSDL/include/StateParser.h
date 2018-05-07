#pragma once

#include "../outside/tinyxml.h"
#include <vector>

#include "../include/GameObject.h"


class StateParser
{
public:
	StateParser();
	~StateParser();

	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:

	bool parseObjects(TiXmlElement* pRoot, std::vector<GameObject*> *pObjects);

	bool parseTextures(TiXmlElement* pRoot, std::vector<std::string> *pTextureIDs);
};

