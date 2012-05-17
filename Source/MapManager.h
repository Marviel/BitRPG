/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_MapManager_h
#define BitRPG_MapManager_h

#include "JSONValue.h"

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <map>

class Entity;


class MapManager : public sf::Drawable
{
public:
	MapManager(int width, int height);
	
	void loadMap(JSONValue &mapObject);
	
	void draw(sf::RenderTarget &target,
			  sf::RenderStates states) const;
	
	typedef boost::shared_ptr<Entity> EntityPtr;
	void addEntity(EntityPtr entity, int zOrder=0);
	
private:
	boost::scoped_ptr<sf::RenderTexture> mapTexture;
	boost::scoped_ptr<sf::Sprite> mapSprite;
	boost::scoped_ptr<sf::View> mapView;
	
	std::multimap<int, EntityPtr> entities;
	
	// Pixel dimensions of map tile
	int tileWidth, tileHeight;
	
	// Tile dimensions of map
	int mapWidth, mapHeight;
};

#endif
