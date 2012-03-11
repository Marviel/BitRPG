//
//  World.cpp
//  Bit
//
//  Created by Andrew Belt on 3/1/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "World.h"
#include "Game.h"
#include <assert.h>
#include <stdio.h>


World::World()
{
}


void World::loadMap(const char *filename)
{
    // Read a JSON file
    
    jsonRoot.loadFromFile(filename);
    
    // Get dimension data
    
    assert(jsonRoot["orientation"].getString() == std::string("orthogonal"));
    
    mapWidth = getJsonInteger(jsonRoot, "width");
    mapHeight = getJsonInteger(jsonRoot, "height");
    tileWidth = getJsonInteger(jsonRoot, "tilewidth");
    tileHeight = getJsonInteger(jsonRoot, "tileheight");
    
    
    // Get tileset array
    
    JsonBox::Value jsonTilesets = jsonRoot["tilesets"];
    assert(jsonTilesets.isArray());
    
    JsonBox::Array tilesetArray = jsonTilesets.getArray();
    
    // Create each tileset
    
    for (JsonBox::Array::iterator tilesetIterator = tilesetArray.begin();
         tilesetIterator < tilesetArray.end(); ++tilesetIterator)
    {
        // Create a tileset and find its firstGid
        
        Tileset *tileset = new Tileset(*tilesetIterator);
        
        tilesets.insert(std::pair<int, Tileset>(tileset->firstGid, *tileset));
    }
    
    
    // Get layer array
    
    JsonBox::Value jsonLayers = jsonRoot["layers"];
    assert(jsonLayers.isArray());
    
    JsonBox::Array layerArray = jsonLayers.getArray();
    
    // Create each layer
    
    for (JsonBox::Array::iterator layerIterator = layerArray.begin();
         layerIterator < layerArray.end(); ++layerIterator)
    {
        Layer *layer = new Layer(*layerIterator);
        layers.push_back(*layer);
    }
}


int World::getJsonInteger(JsonBox::Value &root, const char *key){
    JsonBox::Value value = root[key];
    
    assert(value.isInteger());
    return value.getInt();
}


void World::draw(SDL_Surface* destination)
{
    // Iterate through each layer bottom-to-top
    
    for (std::deque<Layer>::iterator layerIterator = layers.begin();
         layerIterator < layers.end(); ++layerIterator)
    {
        // Draw layer onto destination surface
        
        for (int y = 0; y < layerIterator->layerHeight; ++y)
        {
            for (int x = 0; x < layerIterator->layerWidth; ++x)
            {
                // Hey look, a bird's nest!
                
                int tileIndex = x + layerIterator->layerWidth * y;
                int gid = layerIterator->tileGids[tileIndex];
                
                // A zero gid means null
                
                if (gid == 0)
                    continue;
                
                Tileset *tileset = getTileset(gid);
                Tile *tile = tileset->getTile(gid);
                
                // Calculate position
                
                SDL_Rect positionRect;
                positionRect.x = tileWidth * x;
                positionRect.y = tileHeight * y;
                positionRect.w = tileWidth;
                positionRect.h = tileHeight;
                
                // Blit to destination surface
                
                SDL_BlitSurface(tileset->surface, &tile->rect,
                                destination, &positionRect);
            }
        }
    }
}


void World::clearMap()
{
    tilesets.clear();
    layers.clear();
}


World::Tileset *World::getTileset(int tileGid)
{
    // Finds the tileset with the greatest firstGid less than tileGid
    
    std::map<int, Tileset>::iterator tilesetIt = tilesets.upper_bound(tileGid);
    tilesetIt--;
    
    return &tilesetIt->second;
}


bool World::isCollision(int x, int y)
{
    // Check each layer for a collision tile at the given coordinate
    
    for (std::deque<Layer>::iterator layerIterator = layers.begin(); layerIterator < layers.end(); layerIterator++)
    {
        Tile *tile = layerIterator->getTile(x, y);
        
        if (tile && tile->collides)
            return true;
    }
    
    return false;
}


World::~World()
{
    clearMap();
}


// World::Tileset

World::Tileset::Tileset(JsonBox::Value jsonTileset)
{
    firstGid = getJsonInteger(jsonTileset, "firstgid");
    
    // Load tileset surface from file
    
    const char *imageFilename = jsonTileset["image"].getString().c_str();
    surface = game->cache.loadFile(imageFilename, false);
    
    std::string transparentColor = jsonTileset["transparentcolor"].getString();
    setTransparency(transparentColor);
    
    // Total width of the tileset in pixels
    
    int totalWidth = getJsonInteger(jsonTileset, "imagewidth");
    int totalHeight = getJsonInteger(jsonTileset, "imageheight");
    
    // Margin and spacing in pixels
    
    int margin = getJsonInteger(jsonTileset, "margin");
    int spacing = getJsonInteger(jsonTileset, "spacing");
    
    // Pixel dimensions of each tile
    
    int pixelWidth = getJsonInteger(jsonTileset, "tilewidth");
    int pixelHeight = getJsonInteger(jsonTileset, "tileheight");
    
    
    // Number of tiles per dimension of the tileset
    
    int tilesetWidth = (totalWidth + spacing - 2 * margin) / (pixelWidth + spacing);
    assert(totalWidth == tilesetWidth * pixelWidth + (tilesetWidth - 1) * spacing + 2 * margin);
    
    int tilesetHeight = (totalHeight + spacing - 2 * margin) / (pixelHeight + spacing);
    assert(totalHeight == tilesetHeight * pixelHeight + (tilesetHeight - 1) * spacing + 2 * margin);
    
    // Total number of tiles in the tileset
    
    tilesetSize = tilesetWidth * tilesetHeight;
    
    
    // Set properties of each tile
    
    for (int y = 0; y < tilesetHeight; ++y)
    {
        for (int x = 0; x < tilesetWidth; ++x)
        {
            // Set position
            
            int pixelX = margin + x * (pixelWidth + spacing);
            int pixelY = margin + y * (pixelHeight + spacing);
            Tile *tile = new Tile(pixelX, pixelY, pixelWidth, pixelHeight);
            
            tiles.push_back(*tile);
        }
    }
    
    // Set individual tile properties
    
    JsonBox::Value jsonTileProperties = jsonTileset["tileproperties"];
    
    assert(jsonTileProperties.isObject());
    JsonBox::Object tilePropertiesObject = jsonTileProperties.getObject();
    
    for (JsonBox::Object::iterator tilePropertiesIterator = tilePropertiesObject.begin(); tilePropertiesIterator != tilePropertiesObject.end(); tilePropertiesIterator++)
    {
        // Get gid from json object key
        
        int gid = atoi(tilePropertiesIterator->first.c_str());
        assert(gid > 0);
        Tile *tile = getTile(gid);
        
        // Collisions
        
        if(tilePropertiesIterator->second["collide"].getString() == "true")
            tile->collides = true;
    }
}


World::Tile *World::Tileset::getTile(int gid)
{
    int index = gid - firstGid;
    
    // Make sure index is within range of the tile deque
    assert(0 <= index && index < tilesetSize);
    
    return &(tiles[index]);
}


void World::Tileset::setTransparency(std::string hexTriplet)
{
    // Convert hex triplet string to integers
    
    int red, green, blue;
    int r = sscanf(hexTriplet.c_str(), "#%2x%2x%2x", &red, &green, &blue);
    
    // Make sure the hex string was the correct format
    
    assert(r == 3);
    
    // Set color as transparent
    
    Uint32 color = SDL_MapRGB(surface->format, red, green, blue);
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color);
}


World::Tileset::~Tileset()
{
    tiles.clear();
}


// World::Tile

World::Tile::Tile(int x, int y, int w, int h, bool collides)
{
    rect.x = x; rect.y = y;
    rect.w = w; rect.h = h;
    this->collides = collides;
}



// World::Layer

World::Layer::Layer(JsonBox::Value jsonLayer)
{
    // Layer dimensions in number of tiles
    
    layerWidth = getJsonInteger(jsonLayer, "width");
    layerHeight = getJsonInteger(jsonLayer, "height");
    
    layerSize = layerWidth * layerHeight;
    
    // Get layer data array
    
    JsonBox::Value jsonData = jsonLayer["data"];
    assert(jsonData.isArray());
    
    JsonBox::Array jsonDataArray = jsonData.getArray();
    assert(jsonDataArray.size() >= layerSize);
    
    // Iterate through each tile
    
    tileGids.resize(layerSize);
    JsonBox::Value tileGid;
    
    for (int i = 0; i < layerSize; ++i)
    {
        tileGid = jsonDataArray[i];
        assert(tileGid.isInteger());
        
        tileGids[i] = tileGid.getInt();
    }
}


World::Tile *World::Layer::getTile(int x, int y)
{
    // Check if the coordinates are in the layer rectangle
    
    // If a feature is added in which layers can be placed at points other
    // than (0, 0) on the world map, this assertion must be changed to
    // account for the possible offset.
    
    //assert(0 <= x && x < layerWidth && 0 <= y && y < layerHeight);
    
    if (0 <= x && x < layerWidth && 0 <= y && y < layerHeight)
        return NULL;
    
    int gid = tileGids[x + layerWidth * y];
    
    // Return NULL if there is no tile at that position
    
    if (gid == 0)
        return NULL;
    
    Tileset *tileset = game->world.getTileset(gid);
    return tileset->getTile(gid);
}


World::Layer::~Layer()
{
    tileGids.clear();
}









