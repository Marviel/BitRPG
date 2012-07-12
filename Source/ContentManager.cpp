/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "ContentManager.h"
#include "Exception.h"

#include <fstream>
#include <sstream>

using namespace sf;


Image *ContentManager::loadImage(std::string filename)
{
	// Check if image has already been loaded
	
	std::map<std::string, Image>::iterator imageIt = images.find(filename);
	
	if (imageIt != images.end())
	{
		return &imageIt->second;
	}
	else
	{
		// Create a new image
		
		Image *image = new Image;
		bool success = image->loadFromFile(filename);
		
		if (!success)
			throw bit::Exception("Could not load file " + filename);
		
		// Insert image into images map
		
		images.insert(std::pair<std::string, Image>(filename, *image));
		return image;
	}
}


boost::shared_ptr<sf::Texture> ContentManager::loadTexture(std::string filename,
		const IntRect &area)
{
	// Get image from filename
	
	Image *image = loadImage(filename);
	
	// Create new texture from image
	
	Texture *texture = new Texture;
	texture->loadFromImage(*image, area);
	
	return boost::shared_ptr<Texture>(texture);
}


std::string ContentManager::loadFile(std::string filename)
{
	// Open file stream
	
	std::ifstream file;
	file.open(filename.c_str());
	
	// Dump entire file into buffer
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	
	return buffer.str();
}

