/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "AssetManager.h"
#include "Exception.h"

#include <string>
#include <fstream>
#include <sstream>

#include <unistd.h>
#include <iostream>

using namespace bit;
using namespace sf;
using namespace std;


AssetManager::AssetManager()
{
	// TODO
	// Resource path should be generated by platform and working directory
	
	cout << getcwd(NULL, 0) << endl;
	
	resourcePath = "/Users/andrew/Dev/C++/Bit/BitRPG";
}


boost::shared_ptr<Image> AssetManager::loadImage(string filename)
{
	// Check if image has already been loaded
	
	map<string, ImagePtr>::iterator imageIt;
	imageIt = images.find(filename);
	
	if (imageIt != images.end())
	{
		return imageIt->second;
	}
	else
	{
		string filepath = resourcePath + filename;
		
		// Create a new image
		
		ImagePtr image(new Image);
		bool success = image->loadFromFile(filepath);
		
		if (!success)
			throw bit::Exception("Could not load file " + filename);
		
		// Insert image into images map
		
		
		pair<string, ImagePtr> imagePair(filename, image);
		images.insert(imagePair);
		return image;
	}
}


sf::TexturePtr AssetManager::loadTexture(string filename,
		const IntRect &area)
{
	// Get image from filename
	
	ImagePtr image = loadImage(filename);
	
	// Create new texture from image
	
	sf::TexturePtr texture(new Texture);
	texture->loadFromImage(*image, area);
	
	return texture;
}


string AssetManager::loadFile(string filename)
{
	string filepath = resourcePath + filename;
	
	// Open file stream
	
	ifstream file;
	file.open(filepath.c_str());
	
	// Dump entire file into buffer
	
	stringstream buffer;
	buffer << file.rdbuf();
	
	return buffer.str();
}

