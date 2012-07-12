/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "MapManager.h"
#include "Entity.h"
#include "Exception.h"

using namespace sf;


MapManager::MapManager(int width, int height)
{
	// New View
	
	mapView.reset(new View);
	mapView->setSize(width, height);
	mapView->setCenter(0.0f, 0.0f);
	
	// New RenderTexture
	
	mapTexture.reset(new RenderTexture);
	mapTexture->create(width, height);
	mapTexture->setView(*mapView);
	
	// New Sprite
	
	mapSprite.reset(new Sprite(mapTexture->getTexture()));
}


void MapManager::loadMap(JSONValue &mapObject)
{
	if (mapObject["orientation"].toString() != "orthogonal")
		throw bit::Exception("Map must be orthogonal");
	
	// Set the tile dimensions
	
	tileWidth = mapObject["tilewidth"].toInteger();
	tileHeight = mapObject["tileheight"].toInteger();
	
	mapWidth = mapObject["width"].toInteger();
	mapHeight = mapObject["height"].toInteger();
	
	// TODO
	// Build tilesets
}


void MapManager::draw(RenderTarget &target, RenderStates states) const
{
	mapTexture->clear();
	
	// Draw entities and tiles onto the map texture
	
	for (std::multimap<int, EntityPtr>::const_iterator entityIt =
		 entities.begin(); entityIt != entities.end(); entityIt++)
	{
		// Draw entity
		
		mapTexture->draw(*entityIt->second);
	}
	
	mapTexture->display();
	
	// Draw the map sprite onto the window
	
	target.draw(*mapSprite, states);
}


void MapManager::addEntity(EntityPtr entity, int zOrder)
{
	entities.insert(std::pair<int, EntityPtr>(zOrder, entity));
}

