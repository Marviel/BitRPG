/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "Entity.h"

using namespace sf;


Entity::Entity(boost::shared_ptr<sf::Texture> texture)
{
	sprite.reset(new Sprite(*texture));
	this->texture = texture;
}


void Entity::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(*sprite, states);
}