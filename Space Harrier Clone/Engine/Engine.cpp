#include "Engine.h"

#pragma comment( lib, "Engine/SDL2/libx86/SDL2.lib" )
#pragma comment( lib, "Engine/SDL2_image/libx86/SDL2_image.lib")
#pragma comment( lib, "Engine/SDL2_mixer/libx86/SDL2_mixer.lib")
#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"
#include "SDL2_mixer/include/SDL_mixer.h"
#include "globals.h"
#include "gameConfig.h"
#include "TimeController.h"
#include "InputController.h"
#include "AudioController.h"
#include "SceneManager.h"
#include "PrefabsFactory.h"
#include "GameObjectsManager.h"
#include "ComponentsManager.h"



Engine* engine = nullptr;

Engine::Engine()
{
	time = new TimeController();
	input = new InputController();
	audio = new AudioController();
	sceneManager = new SceneManager();
	prefabsFactory = new PrefabsFactory();
	gameObjectsManager = new GameObjectsManager();
	componentsManager = new ComponentsManager();
}


Engine::~Engine()
{
	delete componentsManager;
	componentsManager = nullptr;
	delete gameObjectsManager;
	gameObjectsManager = nullptr;
	delete prefabsFactory;
	prefabsFactory = nullptr;
	delete sceneManager;
	sceneManager = nullptr;	
	delete audio;
	audio = nullptr;
	delete input;
	input = nullptr;
	delete time;
	time = nullptr;
}


bool Engine::init() const
{
	// Initialization flag
	bool success = true;

	success &= initSDL();

	if (success)
	{
		success &= initEngine();
	}
	return success;
}


void Engine::handleEvents(bool& shouldQuit) const
{
	// Event handler
	SDL_Event e;

	// Clear Input states
	input->clearStates();

	while (SDL_PollEvent(&e))
	{
		// User requested quit
		if (e.type == SDL_QUIT)
		{
			shouldQuit = true;
		}
		else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			input->setKeyDown(e.key.keysym.scancode);
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			input->setKeyUp(e.key.keysym.scancode);
		}
	}
}


void Engine::loop() const
{
	// Main loop flag
	bool quit = false;

	// While application is running
	while (!quit)
	{
		time->updateTime();

		handleEvents(quit);

		sceneManager->refreshScenes();

		gameObjectsManager->update();

		componentsManager->update();
	}
}


void Engine::close() const
{
	// Delete all ComponentManagers
	componentsManager->close();

	// Unload scene
	sceneManager->close();

	// Quit SDL subsystems
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


bool Engine::initSDL() const
{
	// Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		OutputLog("ERROR: SDL could not initialize! SDL Error: %s", SDL_GetError());
		success = false;
	}
	else
	{
		// Initialize PNG loading
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
		{
			OutputLog("ERROR: SDL_Image could not initialize! SDL_image Error: %s", IMG_GetError());
			success = false;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			OutputLog("ERROR: SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
			success = false;
		}
		Mix_AllocateChannels(16);

	}
	return success;
}


bool Engine::initEngine() const
{
	// Initialization flag
	bool success = true;

	if (!scenesConfig())
	{
		OutputLog("ERROR: Failed to setup scenes!");
		success = false;
	}
	else
	{
		if (!prefabsConfig())
		{
			OutputLog("ERROR: Failed to setup prefabs!");
			success = false;
		}
		else
		{
			// Initialize the ComponentsManager
			success &= componentsManager->init();
		}
	}

	return success;
}
