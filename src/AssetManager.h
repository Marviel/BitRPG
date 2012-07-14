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
#include <boost/filesystem.hpp>


namespace bit
{
	class AssetManager
	{
	public:
		AssetManager();
		
		sf::ImagePtr loadImage(const std::string &filename);
		sf::TexturePtr loadTexture(const std::string &filename,
			const sf::IntRect &area=sf::IntRect());
		
		std::string loadText(const std::string &filename);
		
	private:
		std::string getAbsoluteFilename(const std::string &filename);
		
		boost::filesystem::path resourcePath;
		
		std::map<std::string, sf::ImagePtr> images;
	};
}


#endif
