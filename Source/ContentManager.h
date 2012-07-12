/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_ContentManager_h
#define BitRPG_ContentManager_h

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>


class ContentManager
{
public:
	boost::shared_ptr<sf::Texture> loadTexture(std::string filename, const sf::IntRect &area=sf::IntRect());
	
	std::string loadFile(std::string filename);
	
private:
	sf::Image *loadImage(std::string filename);
	
	std::map<std::string, sf::Image> images;
};


#endif
