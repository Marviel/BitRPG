/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_BitRPG_h
#define BitRPG_BitRPG_h

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>


namespace bit
{
	class Application;
	class AssetManager;
	class ScriptManager;
	class DisplayManager;
	class MapManager;
	class Entity;
	class JSONValue;
	class MapLayer;
	class ScriptObject;
	class ScriptClass;
	
	class MapTile;
	
	typedef boost::shared_ptr<Application> ApplicationPtr;
	typedef boost::shared_ptr<AssetManager> AssetManagerPtr;
	typedef boost::shared_ptr<ScriptManager> ScriptManagerPtr;
	typedef boost::shared_ptr<DisplayManager> DisplayManagerPtr;
	typedef boost::shared_ptr<MapManager> MapManagerPtr;
	typedef boost::shared_ptr<Entity> EntityPtr;
	typedef boost::shared_ptr<MapTile> MapTilePtr;
	typedef boost::shared_ptr<MapLayer> MapLayerPtr;
}


namespace sf
{
	typedef boost::shared_ptr<sf::Image> ImagePtr;
	typedef boost::shared_ptr<sf::Texture> TexturePtr;
	typedef boost::shared_ptr<sf::Sprite> SpritePtr;
}

#endif
