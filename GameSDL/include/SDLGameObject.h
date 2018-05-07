#ifndef __SDL_GAME_OBJECT__
#define __SDL_GAME_OBJECT__

#include "GameObjectFactory.h"
#include "InputModule.h"

class SDLGameObject : public GameObject
{
protected:

	Vector2D _position;
	Vector2D _velocity;
	Vector2D _acceleration;
	std::string _textureID;	
	
	int _width;
	int _height;
	float _scale;
	bool _flip;

	int _currentRow;
	int _currentFrame;
	int _numFrames;

	void handleInput();

public:

	SDLGameObject();

	Vector2D position();	
	Vector2D velocity();
	Vector2D acceleration();
	
	int height();
	int width();
	float scale();
	int flip();

	void setPosition(int x, int y);
	void setVelocity(int x, int y);
	void setAcceleration(int x, int y);	
	
	virtual void load(const LoaderParams *parameters);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
};

class SDLGameObjectCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new SDLGameObject(); }
};


#endif