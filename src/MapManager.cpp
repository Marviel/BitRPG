/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapManager.h"
#include "Exception.h"
#include "Entity.h"
#include "AssetManager.h"
#include "MapTile.h"
#include "MapLayer.h"

#include <string>
#include <sstream>

using namespace bit;
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
	
	// Build tilesets
	
	JSONValue tilesetArray = mapObject["tilesets"];
	int tilesetLength = tilesetArray.arrayLength();
	
	for (int index = 0; index < tilesetLength; ++index)
	{
		// Create tileset
		
		JSONValue tilesetObject = tilesetArray[index];
		loadTileset(tilesetObject);
	}
	
	// Build layers
	
	JSONValue layerArray = mapObject["layers"];
	int layerLength = layerArray.arrayLength();
	
	for (int index = 0; index < layerLength; ++index)
	{
		// Create layer
		
		JSONValue layerObject = layerArray[index];
		MapLayerPtr mapLayer(new MapLayer(this, layerObject));
		
		// The index (i.e. the order which the layer appears, zero-based)
		// will be its z-order number
		
		layers.insert(std::pair<int, MapLayerPtr>(index, mapLayer));
	}
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
	
	// TEMP
	
	for (std::multimap<int, MapLayerPtr>::const_iterator layerIt =
		 layers.begin(); layerIt != layers.end(); layerIt++)
	{
		mapTexture->draw(*layerIt->second);
	}
	
	mapTexture->display();
	
	// Draw the map sprite onto the window
	
	target.draw(*mapSprite, states);
}


void MapManager::addEntity(EntityPtr entity, int zOrder)
{
	entities.insert(std::pair<int, EntityPtr>(zOrder, entity));
}


void MapManager::loadTileset(JSONValue &tilesetObject)
{
	// Extract most of the JSONValue data
	
	//std::string name = tilesetObject["name"].toString();
	int firstGid = tilesetObject["firstgid"].toInteger();
	
	std::string imageFilename = tilesetObject["image"].toString();
	boost::shared_ptr<Image> image;
	image = launcher->contentManager->loadImage(imageFilename);
	
	int imageWidth = tilesetObject["imagewidth"].toInteger();
	int imageHeight = tilesetObject["imageheight"].toInteger();
	int tileWidth = tilesetObject["tilewidth"].toInteger();
	int tileHeight = tilesetObject["tileheight"].toInteger();
	int margin = tilesetObject["margin"].toInteger();
	int spacing = tilesetObject["spacing"].toInteger();
	
	// Check the math of the tileset dimensions
	
	if ((imageWidth + spacing - 2 * margin) % (spacing + tileWidth) != 0)
		throw bit::Exception("Tileset image '" + imageFilename +
							 "' does not have a valid width");
	
	if ((imageHeight + spacing - 2 * margin) % (spacing + tileHeight) != 0)
		throw bit::Exception("Tileset image '" + imageFilename +
							 "' does not have a valid height");
	
	// Create the map dimensions of the tileset.
	// These correspond to the number of tiles
	// across the image in each dimension.
	
	int mapWidth = (imageWidth + spacing - 2 * margin) / (spacing + tileWidth);
	int mapHeight = (imageHeight + spacing - 2 * margin) / (spacing + tileHeight);
	int mapLength = mapWidth * mapHeight;
	
	for (int index = 0; index < mapLength; ++index)
	{
		int x = index % mapWidth;
		int y = index / mapWidth;
		
		IntRect rect(margin + (tileWidth + spacing) * x,
					 margin + (tileHeight + spacing) * y,
					 tileWidth, tileHeight);
		
		TexturePtr texture(new Texture);
		texture->loadFromImage(*image, rect);
		
		// Create MapTile
		
		MapTilePtr tile(new MapTile);
		tile->texture = texture;
		
		// Add texture to vector
		
		tiles.insert(std::pair<int, MapTilePtr>(firstGid + index, tile));
	}
}


MapTilePtr MapManager::getTile(int gid)
{
	std::multimap<int, MapTilePtr>::iterator tileIt = tiles.find(gid);
	
	if (tileIt == tiles.end())
	{
		std::stringstream message;
		message << "Tile #" << gid << " does not exist";
		throw bit::Exception(message.str());
	}
	
	return tileIt->second;
}



