#include "../include/Game.h"

#include "../include/ErrorHandler.h"
#include "../include/MainMenuState.h"
#include "../include/MenuButton.h"
#include "../include/Enemy.h"
#include "../include/Player.h"
#include "../include/Cursor.h"
#include "../include/AnimatedGraphic.h"


Game* Game::instance = NULL;

Game* Game::Instance()
{
	if(instance == NULL) instance = new Game();
	return instance;	
}

Game::Game(){
	gameRunning = false;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	this->frame = 0;
	int flags = 0;
	if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Success: SDL initializated.\n";

		// Init window
		gameWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (gameWindow != NULL)
		{
			std::cout << "Success: window created.\n";

			// create renderer
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);

			if (gameRenderer != NULL)
			{
				std::cout << "Success: renderer created.\n";
				SDL_SetRenderDrawColor(gameRenderer, 0,0,0, 255);

				// IMG Init
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (IMG_Init(imgFlags) == imgFlags) 
				{
					std::cout << "Success: IMG initialized.\n";
				}
				else std::cout << "Error: IMG failed initialization.\n";

				// Register types
				GameObjectFactory::registerType("MenuButton", new MenuButtonCreator());
				GameObjectFactory::registerType("Cursor", new CursorCreator());
				GameObjectFactory::registerType("Player", new PlayerCreator());
				GameObjectFactory::registerType("Enemy", new EnemyCreator());
				GameObjectFactory::registerType("SDLGameObject", new SDLGameObjectCreator());
				GameObjectFactory::registerType("AnimatedGraphic", new AnimatedGraphicCreator());

				// Input Init
				if (InputModule::Init())
					std::cout << "Success: Input initialized!\n";
				// Joystick Init
				if(InputModule::InitJoysticks())
					std::cout << "Success: Joysticks initialized!\n";
				


				// State machine Init
				this->_stateMachine = new GameStateMachine();
				this->_stateMachine->changeState(new MainMenuState());			
			}
			else
			{
				std::cout << "Error: renderer creation.\n";
			}
		}
		else
		{
			std::cout << "Error: window creation.\n";
		}
	}
	else
	{
		std::cout << "Error: SDL initialization.\n";
		return false;
	}

	std::cout << "Program initialized with no errors.\n";
	gameRunning = true;
	return true;
}


void Game::render()
{
	if (SDL_RenderClear(gameRenderer) != 0)	LOG_ERROR("SDL: " << SDL_GetError());	// clear renderer

	this->_stateMachine->render();

	SDL_RenderPresent(gameRenderer); // draw screen
}

void Game::update()
{
	frame += 1;
	if (frame > 9000000000000000000) frame = 0;

	// SDL_SetRenderDrawColor(gameRenderer, frame % 256, frame % 128, frame % 64, 255);

	if (InputModule::CloseWindowRequest())
	{
		this->gameRunning = false;
		return;
	}

	this->_stateMachine->update();
}

void Game::clean()
{
	InputModule::Clean();
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	SDL_Quit();
	this->gameRunning = false;
	std::cout << "Game finished with no errors.\n";
}

void Game::handleEvents()
{
	InputModule::Update();
}

bool Game::isRunning()
{
	return gameRunning;
}

GameStateMachine * Game::stateMachine()
{
	return this->_stateMachine;
}

