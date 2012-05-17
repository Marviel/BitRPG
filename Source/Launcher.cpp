/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "Launcher.h"
#include "ContentManager.h"
#include "ScriptEngine.h"
#include "DisplayManager.h"
#include "JSONValue.h"
#include "Entity.h"
#include "Exception.h"
#include "MapManager.h"

#include <SFML/System.hpp>
#include <string>

using boost::shared_ptr;
using std::string;


Launcher::Launcher()
{
	contentManager.reset(new ContentManager);
	scriptEngine.reset(new ScriptEngine);
	displayManager.reset(new DisplayManager);
}


void Launcher::run()
{
	loadConfig();
	
	// TEMP
	// Launch ScriptEngine thread and load init script
	// For now we'll just place some objects onto the MapManager
	
	shared_ptr<sf::Texture> playerTexture = contentManager->loadTexture("/Users/andrew/Dev/C++/Bit/Bit/Resources/player.png");
	shared_ptr<Entity> player(new Entity(playerTexture));
	
	displayManager->mapManager->addEntity(player, 1);
	
	// End TEMP
	
	displayManager->run();
}


void Launcher::loadConfig()
{
	// Load config.json into configValue
	
	std::string configData = contentManager->loadFile("/Users/andrew/Dev/C++/Bit/BitRPG/config.json");
	JSONValue configValue = scriptEngine->parseJSON(configData);
	
	// Create window
	
	JSONValue windowValue = configValue["window"];
	displayManager->createWindow(windowValue);
}

