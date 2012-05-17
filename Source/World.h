//
//  World.h
//  Bit
//
//  Created by Andrew Belt on 3/1/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Bit_World_h
#define Bit_World_h

#include <SDL/SDL.h>
#include <JsonBox.h>
#include <deque>
#include <map>
#include <vector>


class Entity;
class Hero;


class World
{
public:
    World();
    ~World();
    
    void loadMap(const char *filename);
    void clearMap();
    void draw(SDL_Surface *destination);
    
    /**
     * Represents a sprite sheet with configuration settings
     */
    struct Tileset;
    
    /**
     * Represents a single tile on the sprite sheet
     */
    struct Tile;
    
    struct Layer;
    
    // Returns tileset containing the tileGid
    Tileset *getTileset(int tileGid);
    bool isCollision(int x, int y);
    
    // Pixels per tile
    int tileWidth, tileHeight;
    
private:
    // Quick JSON interfaces
    
    JsonBox::Value jsonRoot;
    static int getJsonInteger(JsonBox::Value &root, const char *key);
    
    // Tiles per map
    int mapWidth, mapHeight;
    
    // Array containing each tileset used in the map
    std::map<int, Tileset> tilesets;
    std::deque<Layer> layers;
};


struct World::Tileset
{
    Tileset(JsonBox::Value jsonTileset);
    ~Tileset();
    
    Tile *getTile(int gid);
    
    /**
     * Converts a hex color triplet into a color key for the surface
     *
     * Example: "#0022FF"  ->  0, 34, 255
     * This only works if the image was loaded as an RGB surface. This can be done with CacheLoader::loadFile(filename, false)
     */
    void setTransparency(std::string hexTriplet);
    
    SDL_Surface *surface;
    std::deque<Tile> tiles;
    
    int firstGid;
    int tilesetSize;
};


struct World::Tile
{
    Tile(int x, int y, int w, int h, bool collides = false);
    SDL_Rect rect;
    bool collides;
};


struct World::Layer
{
    Layer(JsonBox::Value jsonLayer);
    ~Layer();
    
    Tile *getTile(int x, int y);
    
    int layerWidth, layerHeight, layerSize;
    std::vector<int> tileGids;
};

#endif



