#include <stdio.h>
#include "Engine.h"
#include "globals.h"
#include "SDL2/include/SDL_main.h"
#pragma comment( lib, "Engine/SDL2/libx86/SDL2main.lib" )


int main(int argc, char* args[])
{
	OutputLog("INFO: Start.");
	OutputLog("INFO: Engine will be created.");
	engine = new Engine();

	OutputLog("INFO: Engine will be initialized.");
	if (!engine->init())
	{
		OutputLog("ERROR: Failed to initialize Engine!");
	}
	else
	{	
		OutputLog("INFO: Engine will begin looping.");
		engine->loop();
	}

	OutputLog("INFO: Engine will close.");
	engine->close();
	OutputLog("INFO: Engine will be deleted.");
	delete engine;
	engine = nullptr;

	OutputLog("INFO: End.");
 	return 0;
}
