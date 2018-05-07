#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
private:
	// store the single _instance
	static TextureManager* instance;

	// texture map
	std::map <std::string, SDL_Texture*> textureMap;

	TextureManager(){}
	~TextureManager(){}
public:
	
	static TextureManager* Instance();

	// load texture
	bool load(std::string fileName, std::string id, SDL_Renderer *renderer);

	// draw
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer, float scaleFactor = 1 , bool flip = false);

	// draw frame
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, float scaleFactor = 1 , bool flip = false);

	// clear from texture map
	void eraseTexture(std::string id);
	
};

#endif