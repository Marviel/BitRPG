/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
public:
	Entity(boost::shared_ptr<sf::Texture> texture);
	
	void draw(sf::RenderTarget &target,
			  sf::RenderStates states) const;
	
private:
	boost::scoped_ptr<sf::Sprite> sprite;
	boost::shared_ptr<sf::Texture> texture;
};


#endif
