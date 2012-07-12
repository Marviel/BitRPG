/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapManager_h
#define BitRPG_MapManager_h

#include "BitRPG.h"
#include "JSONValue.h"

#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>
#include <map>

class Entity;
class MapTile;


namespace bit
{
	class MapManager : public sf::Drawable
	{
	public:
		MapManager(int width, int height);
		
		void loadMap(JSONValue &mapObject);
		MapTilePtr getTile(int gid);
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		void addEntity(EntityPtr entity, int zOrder=0);
		
		// Pixel dimensions of map tile
		int tileWidth, tileHeight;
		
		// Tile dimensions of map
		int mapWidth, mapHeight;
		
	private:
		void loadTileset(JSONValue &tilesetObject);
		
		boost::scoped_ptr<sf::RenderTexture> mapTexture;
		boost::scoped_ptr<sf::Sprite> mapSprite;
		boost::scoped_ptr<sf::View> mapView;
		
		// Drawable objects
		
		// <z-order, entity>
		std::multimap<int, EntityPtr> entities;
		
		// <z-order, mapLayer>
		std::multimap<int, MapLayerPtr> layers;
		
		// <gid, mapTile>
		std::multimap<int, MapTilePtr> tiles;
	};
}

#endif
