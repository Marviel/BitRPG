/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "AssetManager.h"
#include "ScriptManager.h"
#include "DisplayManager.h"
#include "JSONValue.h"
#include "Entity.h"
#include "Exception.h"
#include "MapManager.h"
#include "GameObject.h"

#include <SFML/System.hpp>
#include <string>
#include <iostream>

using namespace bit;


Application::Application()
{
	assetManager.reset(new AssetManager);
	scriptManager.reset(new ScriptManager);
	displayManager.reset(new DisplayManager);
}


void Application::start()
{
	initScriptObjects();
	loadConfig();
	
	// TEMP
	
	std::string mapData = assetManager->loadFile("map.json");
	JSONValue mapObject = scriptManager->parseJSON(mapData);
	displayManager->mapManager->loadMap(mapObject);
	
	// End TEMP
	
	displayManager->run();
}


void Application::initScriptObjects()
{
	// game
	
	scriptManager->registerObject(new GameObject(), "game");
}


void Application::loadConfig()
{
	// Load config.json into configValue
	
	std::string configData = assetManager->loadFile("config.json");
	JSONValue configValue = scriptManager->parseJSON(configData);
	
	// Create window
	
	JSONValue windowValue = configValue["window"];
	displayManager->createWindow(windowValue);
}

