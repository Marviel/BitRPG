//
//  Character.h
//  Bit
//
//  Created by Andrew Belt on 3/1/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Bit_Character_h
#define Bit_Character_h

#include <SDL/SDL.h>
#include "Entity.h"

class CacheLoader;


/**
 * Represents a freely moving living being
 *
 * Examples: players, NPC's, monsters, etc.
 */
class Character : public Entity
{
public:
    Character();
    
    void preLoop();
    void advanceFrame();
    
    void startMoving(int direction);
    void stopMoving();
    bool isMoving();
    
    float speed;
    
private:
    bool moving;
    
    // Cardinal direction index on [0, 4)
    int direction;
    
    int directionX [4];
    int directionY [4];
};


#endif
