#include "..\include\StateParser.h"

#include "../include/Game.h"
#include "../include/GameObjectFactory.h"
#include "../include/ErrorHandler.h"



StateParser::StateParser()
{
}

StateParser::~StateParser()
{
}

bool StateParser::parseState(const char * stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string> *pTextureIDs)
{
	// create the XML document variable
	TiXmlDocument xmlDoc;

	// load the state file
	if (!xmlDoc.LoadFile(stateFile)) {
		LOG_ERROR("TinyXML: " << xmlDoc.ErrorDesc());
		return false;
	}

	// get the root element
	TiXmlElement *pRoot = xmlDoc.RootElement();

	TiXmlElement *pStateRoot = NULL;	
	for (TiXmlElement* i = pRoot->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		if (i->Value() == stateID) {
			pStateRoot = i;
			break;
		}			
	}
	if (pStateRoot == NULL) {
		LOG_ERROR("couldn't find state " << stateID << " in " << stateFile);
		return false;
	}

	TiXmlElement* pTextureRoot = NULL;
	for (TiXmlElement* i = pStateRoot->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		if (i->Value() == (std::string) "TEXTURES") {
			pTextureRoot = i;
			break;
		}
	}
	if (pTextureRoot == NULL) {
		LOG_ERROR("couldn't find \"TEXTURES\" element in " << stateFile);
		return false;
	}
	parseTextures(pTextureRoot, pTextureIDs);

	TiXmlElement* pObjectRoot = NULL;
	for (TiXmlElement* i = pStateRoot->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		if (i->Value() == (std::string) "OBJECTS") {
			pObjectRoot = i;
			break;
		}
	}
	if (pTextureRoot == NULL) {
		LOG_ERROR("couldn't find \"OBJECTS\" element in " << stateFile);
		return false;
	}
	parseObjects(pObjectRoot, pObjects);

	return true;
}

bool StateParser::parseObjects(TiXmlElement * pRoot, std::vector<GameObject*>* pObjects)
{
	if (pRoot == NULL) return false;

	for (TiXmlElement* i = pRoot->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed, flip;
		double scale;
		std::string textureID;

		i->Attribute("x", &x);
		i->Attribute("y", &y);
		i->Attribute("width", &width);
		i->Attribute("height", &height);
		i->Attribute("scale", &scale);
		i->Attribute("numFrames", &numFrames);
		i->Attribute("callbackID", &callbackID);
		i->Attribute("animSpeed", &animSpeed);
		i->Attribute("flip", &flip);

		textureID = i->Attribute("textureID");
		
		// MY_DEBUG(textureID << ": flip = " << flip);
		 MY_DEBUG(textureID << ": numframes = " << numFrames);

		GameObject* pGameObject = GameObjectFactory::create(i->Attribute("type"));
		if (pGameObject == NULL) {
			LOG_ERROR("couldn't create object of type " << i->Attribute("type") << " and textureID " << textureID);
		}		
		if (pGameObject != NULL) {
			pGameObject->load(new LoaderParams(x, y, width, height, textureID, scale, flip, numFrames, callbackID, animSpeed));
			pObjects->push_back(pGameObject);
		}
		
	}
	return true;
}

bool StateParser::parseTextures(TiXmlElement * pRoot, std::vector<std::string>* pTextureIDs)
{
	if (pRoot == NULL) return false;

	for (TiXmlElement* i = pRoot->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		std::string filenameArg = i->Attribute("filename");
		std::string idArg = i->Attribute("ID");

		pTextureIDs->push_back(idArg);

		if (!TextureManager::Instance()->load(filenameArg, idArg, Game::Instance()->getRenderer())) {
			LOG_ERROR("SDL: " << SDL_GetError());
		}		
	}

	return true;
}
