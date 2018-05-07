#include "../include/TextureManager.h"

#include "../include/ErrorHandler.h"
#include "../include/Game.h"


TextureManager* TextureManager::instance = NULL;

TextureManager* TextureManager::Instance()
{
	if(instance == NULL) instance = new TextureManager();
	return instance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *renderer)
{
	// creating surface
	// SDL_ClearError();
	SDL_Surface *tempSurf = IMG_Load(fileName.c_str());
	if(tempSurf == NULL)
	{
		LOG_ERROR("SDL: " + std::string("Fodase"));
		return false;
	}

	// creating texture from surface
	// SDL_ClearError();
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurf);
	if (newTexture == NULL) 
	{
		LOG_ERROR("SDL: " << SDL_GetError());
		return false;
	}


	// freeing surface
	SDL_FreeSurface(tempSurf);

	// adding texture to textureMap
	this->textureMap[id] = newTexture;

	MY_DEBUG("Success: Texture " << id << " loaded.\n");
	return true;
	
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer, float scaleFactor, bool flip)
{
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	sourceRect.x = 0;				
	sourceRect.y = 0;
	sourceRect.w = width;
	sourceRect.h = height;
	
	destRect.x = x;
	destRect.y = y;
	destRect.w = (int) (scaleFactor * width);
	destRect.h = (int) (scaleFactor * height);

	SDL_RendererFlip flag = SDL_FLIP_NONE;
	if (flip == true) flag = SDL_FLIP_HORIZONTAL;
	
	if (width == 0 || height == 0)
		SDL_QueryTexture(this->textureMap[id], NULL, NULL, &sourceRect.w, &sourceRect.h);

	// SDL_ClearError();
	if (SDL_RenderCopyEx(renderer, this->textureMap[id], &sourceRect, &destRect, 0, NULL, flag) == -1)
		LOG_ERROR("SDL: " << SDL_GetError());
		
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, float scaleFactor, bool flip)
{
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	sourceRect.x = width * currentFrame;
	sourceRect.y = height * (currentRow - 1);
	sourceRect.w = width;
	sourceRect.h = height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = (int) (scaleFactor * width);
	destRect.h = (int) (scaleFactor * height);

	SDL_RendererFlip flag = SDL_FLIP_NONE;
	if (flip == true) flag = SDL_FLIP_HORIZONTAL;


	/*if (Game::Instance()->FRAME() % 100 == 0 && id == "tweet")
	{
		std::cout << std::endl;
		MY_DEBUG(id << ": " << "currentFrame = " << currentFrame);

		MY_DEBUG(id << ": " << "srcPos = (" << sourceRect.x << ", " << sourceRect.y << ")");
		MY_DEBUG(id << ": " << "srcDim = (" << sourceRect.w << " x " << sourceRect.h << ")");
		
		MY_DEBUG(id << ": " << "destPos = (" << destRect.x << ", " << destRect.y << ")");
		MY_DEBUG(id << ": " << "destDim = (" << destRect.w << " x " << destRect.h << ")");
	}*/	
	
	
	if (width == 0 || height == 0) {
		SDL_QueryTexture(this->textureMap[id], NULL, NULL, &sourceRect.w, &sourceRect.h);
	}		

	// SDL_ClearError();
	if (SDL_RenderCopyEx(renderer, this->textureMap[id], &sourceRect, &destRect, 0, NULL, flag) == -1) {
		LOG_ERROR(id << ": " << "SDL: " << SDL_GetError());
	}
}
		

void TextureManager::eraseTexture(std::string id)
{
	this->textureMap.erase(id);
}
