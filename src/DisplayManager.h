/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_DisplayManager_h
#define BitRPG_DisplayManager_h

#include "BitRPG.h"

#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>

class MapManager;
class ContentManager;
class JSONValue;


namespace bit
{
	class DisplayManager
	{
	public:
		DisplayManager();
		
		void createWindow(JSONValue &windowValue);
		void run();
		
		MapManagerPtr mapManager;
		
	private:
		void pollEvents();
		void render();
		
		boost::scoped_ptr<sf::RenderWindow> window;
		
		// TEMP
		bool running;
	};
}

#endif
