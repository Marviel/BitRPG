/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_DisplayManager_h
#define BitRPG_DisplayManager_h

#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class MapManager;
class ContentManager;
class JSONValue;


class DisplayManager
{
public:
	DisplayManager();
	
	void createWindow(JSONValue &windowValue);
	void run();
	
	boost::scoped_ptr<MapManager> mapManager;
	
private:
	void pollEvents();
	void render();
	
	boost::scoped_ptr<sf::RenderWindow> window;
	
	// TEMP
	bool running;
};

#endif
