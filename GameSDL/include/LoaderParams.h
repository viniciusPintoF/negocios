#ifndef __LOADER_PARAMS__
#define __LOADER_PARAMS__

class LoaderParams
{
private:
	std::string textureID;
	
	bool flip;
	int numFrames;
	
	int xPos;
	int yPos;

	int width;
	int height;
	float scale;

	// Special atributtes
	int animSpeed; //(AnimatedGraphic)
	int callbackID; // (MenuButton)	


public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, float scaleFactor = 1, bool flip = false, int numFrames= 1, int callbackID = 0, int animSpeed = 0) 
		: 
		xPos(x), 
		yPos(y), 
		width(width), 
		height(height), 
		textureID(textureID), 
		scale(scaleFactor), 
		flip(flip), 
		numFrames(numFrames), 
		callbackID(callbackID), 
		animSpeed(animSpeed)
	{	}
	

	int getX() const { return xPos; }
	int getY() const { return yPos; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	float getScale() const { return scale; }
	bool getFlip() const { return flip; }
	int getNumFrames() const { return numFrames; }
	int getCallbackID() const { return callbackID; }
	int getAnimSpeed() const { return animSpeed; }

	std::string getTextureID() const { return textureID; }

	
};

#endif