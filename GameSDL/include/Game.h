#ifndef _GAME_
#define _GAME_

#include "GameStateMachine.h"

class Game
{
private:

	static Game* instance;

	bool gameRunning;
	long long frame;

	SDL_Window *gameWindow;
	SDL_Renderer *gameRenderer;

	GameStateMachine* _stateMachine;
	
	Game();
	~Game(){}

public:

	static Game* Instance();

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen = false);

	void render();

	void update();

	void handleEvents();

	void clean();

	bool isRunning();

	int FRAME() { return frame; }

	SDL_Renderer* getRenderer() const { return gameRenderer; }

	GameStateMachine* stateMachine();
};

#endif