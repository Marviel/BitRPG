//
//  Entity.cpp
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Entity.h"
#include <assert.h>
#include "Game.h"


Entity::Entity()
{
    surface = NULL;
    
    // Prisoner Zero has escaped
    
    mapX = 0; mapY = 0;
    subX = 0.0; subY = 0.0;
    
    // Prisoner Zero will vacate the human residence,
    // or the human residence will be incinerated
    
    tileX = 0; tileY = 0;
    tileWidth = 0; tileHeight = 0;
    offsetX = 0; offsetY = 0;
    
    // Initialize animation
    
    frameCols = 1;
    frameRows = 1;
    frameRepeat = 1;
    animationStop();
}


void Entity::setSurface(SDL_Surface* surface)
{
    assert(surface != NULL);
    
    this->surface = surface;
    tileX = 0; tileY = 0;
    tileWidth = surface->w;
    tileHeight = surface->h;
}


void Entity::setSurface(SDL_Surface* surface, int tileWidth, int tileHeight, int tileX, int tileY, int offsetX, int offsetY)
{
    assert(surface != NULL);
    
    // Make sure we don't cover an area larger than the surface
    
    assert(tileWidth  * (tileX + 1) <= surface->w);
    assert(tileHeight * (tileY + 1) <= surface->h);
    
    this->surface = surface;
    this->tileX = tileX; this->tileY = tileY;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}


void Entity::draw(SDL_Surface* destination)
{
    assert(surface != NULL);
    assert(destination != NULL);
    
    SDL_Rect crop;
    
    // Save some effort by ignoring animation frame position if we can
    
    if (frameIndex == 0)
    {
        crop.x = tileWidth * tileX;
        crop.y = tileHeight * tileY;
    }
    else
    {
        // Calculate the coordinates of the current frame tile
        
        crop.x = tileWidth  * (tileX + frameIndex % frameCols);
        crop.y = tileHeight * (tileY + frameIndex / frameCols);
    }
    
    crop.w = tileWidth;
    crop.h = tileHeight;

    SDL_Rect position;
    position.x = int(game->world.tileWidth  * (float(mapX) + subX)) + offsetX;
    position.y = int(game->world.tileHeight * (float(mapY) + subY)) + offsetY;
    position.w = tileWidth;
    position.h = tileHeight;
    
    SDL_BlitSurface(surface, &crop, destination, &position);
}


void Entity::advanceFrame()
{
    if (animating)
    {
        // Increment frame repeat index by 1 and check if equal to frame repeat
        
        if (++frameRepeatIndex >= frameRepeat)
        {
            frameRepeatIndex = 0;
            
            // Increment frame by 1, but return to 0 if it goes
            // past the last frame
            
            if (++frameIndex >= frameCols * frameRows)
                frameIndex = 0;
        }
    }
}


bool Entity::setAnimationFormat(int cols, int rows)
{
    // Check if the requested tile size is larger than the surface.
    // That is, the surface must cover the entire tile rectangle.
    assert(tileWidth  * (tileX + cols) <= surface->w);
    assert(tileHeight * (tileY + rows) <= surface->h);
    
    // Set tile properties
    
    frameCols = cols;
    frameRows = rows;
    
    // Reset animation. Things could go wrong if we left it running.
    
    animationStop();
    
    return true;
}


void Entity::setFrameRepeat(int frameRepeat)
{
    assert(frameRepeat >= 1);
    
    this->frameRepeat = frameRepeat;
}


void Entity::animationPlay()
{
    animating = true;
}


void Entity::animationPause()
{
    animating = false;
}


void Entity::animationStop()
{
    animating = false;
    frameIndex = 0;
    frameRepeatIndex = 0;
}





