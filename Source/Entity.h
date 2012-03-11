//
//  Entity.h
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Bit_Entity_h
#define Bit_Entity_h

#include <SDL/SDL.h>


class Entity
{
public:
    Entity();
    
    // Properties
    
    void setSurface(SDL_Surface* surface);
    void setSurface(SDL_Surface* surface, int tileWidth, int tileHeight, int tileX, int tileY, int offsetX = 0, int offsetY = 0);
    
    void setOffset(int x, int y);
    
    // Actions
    
    void draw(SDL_Surface* display);
    void advanceFrame();
    
    // Animations
    
    bool setAnimationFormat(int cols, int rows);
    
    /**
     * Sets the number of frames each sprite is displayed in succession
     */
    void setFrameRepeat(int frameRepeat);
    void animationPlay();
    void animationPause();
    void animationStop();
    
    // Index position sprite on tileset
    int tileX, tileY;

    // Posision to render on world display
    int mapX, mapY;
    
    // Value on [0.0, 1.0) to represent a sprite between tiles
    float subX, subY;
    
protected:
    SDL_Surface* surface;
    
    // Pixel dimensions of first sprite on tileset
    int tileWidth, tileHeight;
    
    // Permanent pixel offset to position the sprite
    // within a map tile grid
    int offsetX, offsetY;
    
private:
    bool animating;
    
    // Columns and rows in the 
    int frameCols, frameRows;
    
    // Index of animation frame
    int frameIndex;
    int frameRepeat, frameRepeatIndex;
};

#endif
