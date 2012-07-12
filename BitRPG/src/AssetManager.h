/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_AssetManager_h
#define BitRPG_AssetManager_h

#include "BitRPG.h"
#include <string>
#include <map>


namespace bit
{
	class AssetManager
	{
	public:
		AssetManager();
		
		sf::ImagePtr loadImage(std::string filename);
		sf::TexturePtr loadTexture(std::string filename,
							   const sf::IntRect &area=sf::IntRect());
		
		std::string loadFile(std::string filename);
		
	private:
		
		std::string resourcePath;
		
		std::map<std::string, sf::ImagePtr> images;
	};
}


#endif
