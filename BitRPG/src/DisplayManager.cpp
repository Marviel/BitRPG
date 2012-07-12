/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "DisplayManager.h"
#include "MapManager.h"
#include "AssetManager.h"
#include "JSONValue.h"
#include "Exception.h"

#include <string>

using namespace bit;
using namespace sf;


DisplayManager::DisplayManager()
{
	// TEMP
	
	running = true;
}


void DisplayManager::createWindow(JSONValue &windowObject)
{
	// Create SFML RenderWindow
	
	int width = windowObject["width"].toInteger();
	int height = windowObject["height"].toInteger();
	
	VideoMode videoMode(width, height, 32);
	std::string title = windowObject["title"].toString();
	Uint32 windowStyle = Style::Titlebar | Style::Close;
	
	window.reset(new RenderWindow(videoMode, title.c_str(), windowStyle));
	
	if (!window)
		throw bit::Exception("Window could not be opened");
	
	// Create MapManager
	
	mapManager.reset(new MapManager(width, height));
	
	// Set framerate limit
	
	unsigned int framerate = windowObject["framerate"].toInteger();
	window->setFramerateLimit(framerate);
}


void DisplayManager::run()
{
	if (!window)
		throw bit::Exception("Window is not opened");
	
	if (!mapManager)
		throw bit::Exception("MapManager is not initialized");
	
	// TEMP
	// Start the poll/render loop
	
	while (running)
	{
		pollEvents();
		render();
	}
}


void DisplayManager::pollEvents()
{
	Event event;
	
	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			running = false;
		}
	}
}


void DisplayManager::render()
{
	window->clear();
	
	// Render MapManager
	
	window->draw(*mapManager);
	window->display();
}
