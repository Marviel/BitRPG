/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameObject.h"
#include "Application.h"
#include "ScriptManager.h"
#include "DisplayManager.h"
#include "MapManager.h"
#include "AssetManager.h"
#include "JSONValue.h"
#include "Exception.h"

#include <string>
#include <iostream>

using namespace bit;
using namespace v8;
using std::string;


GameObject::GameObject()
{
}


Local<Object> GameObject::getObject()
{
	HandleScope handleScope;
	
	// Get empty object to start with
	
	Local<Object> obj = getEmptyObject();
	
	// Add functions
	
	Local<FunctionTemplate> loadMapTemplate = FunctionTemplate::New(loadMap);
	Local<Function> loadMapFunction = loadMapTemplate->GetFunction();
	obj->Set(String::New("loadMap"), loadMapFunction);
	
	return handleScope.Close(obj);
}


Handle<Value> GameObject::loadMap(const v8::Arguments &args)
{
	// Extract arguments
	
	string mapName;
	extractArguments(args, "s", &mapName);
	
	// Get pointer to GameObject
	
	//GameObject *gameObject = reinterpret_cast<GameObject *>(getThis(args));
	
	// Call member function with given arguments
	
	//string mapData = launcher->contentManager->loadFile(mapName + ".json");
	//JSONValue mapObject = launcher->scriptEngine->parseJSON(mapData);
	//launcher->displayManager->mapManager->loadMap(mapObject);
	
	// Return stuff
	
	return Undefined();
}



