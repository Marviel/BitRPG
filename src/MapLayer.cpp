/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapLayer.h"
#include "Exception.h"
#include "JSONValue.h"
#include "MapManager.h"
#include "MapTile.h"

using namespace sf;


/*MapLayer::MapLayer(MapManager *mapManager, JSONValue &layerObject)
{
	// Extract layer data
	
	std::string name = layerObject["name"].toString();
	
	mapX = layerObject["x"].toInteger();
	mapY = layerObject["y"].toInteger();
	mapWidth = layerObject["width"].toInteger();
	mapHeight = layerObject["height"].toInteger();
	int mapLength = mapWidth * mapHeight;
	
	// Extract tile data
	
	JSONValue dataArray = layerObject["data"];
	
	// Check that the number of gids agrees with the map dimensions
	
	if (dataArray.arrayLength() != mapLength)
		throw bit::Exception("Layer does not have the correct number of tiles");
	
	//mapSprites.reserve(mapLength);
	
	// Iterate through each tile gid
	
	for (int index = 0; index < mapLength; ++index)
	{
		int gid = dataArray[index].toInteger();
		
		// If gid is zero, don't make a sprite
		
		if (gid == 0)
			continue;
		
		int pixelX = (mapX + index % mapWidth) * mapManager->tileWidth;
		int pixelY = (mapY + index / mapWidth) * mapManager->tileHeight;
		
		MapTilePtr tile = mapManager->getTile(gid);
		
		SpritePtr tileSprite(new Sprite(*tile->texture));
		tileSprite->setPosition(pixelX, pixelY);
		
		mapSprites.push_back(tileSprite);
	}
}*/


void MapLayer::draw(RenderTarget &target, RenderStates states) const
{
	const FloatRect &rect = target.getView().getViewport();
	
	// Iterate through each map sprite
	
	for (std::vector<SpritePtr>::const_iterator mapSpriteIt =
		 mapSprites.begin(); mapSpriteIt != mapSprites.end(); mapSpriteIt++)
	{
		SpritePtr mapSprite = *mapSpriteIt;
		
		// Draw only if in view
		
		if (rect.intersects(mapSprite->getGlobalBounds()))
		{
			target.draw(*mapSprite);
		}
	}
}




