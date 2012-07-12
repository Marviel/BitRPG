/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_MapTile_h
#define BitRPG_MapTile_h

#include "BitRPG.h"


namespace bit
{
	class MapTile
	{
	public:
		sf::TexturePtr texture;
		bool collides;
	};
}

#endif
