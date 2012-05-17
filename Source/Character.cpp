//
//  Character.cpp
//  Bit
//
//  Created by Andrew Belt on 3/1/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Character.h"
#include "Game.h"


Character::Character()
{
    moving = false;
    direction = 0;
    
    // Set direction index to unit movement
    
    //               N   E   S   W
    //directionX = { 0,  1,  0, -1};
    //directionY = {-1,  0,  1,  0};
    
    directionX[0] = 0;
    directionX[1] = 1;
    directionX[2] = 0;
    directionX[3] = -1;
    
    directionY[0] = -1;
    directionY[1] = 0;
    directionY[2] = 1;
    directionY[3] = 0;
    
    // Speed should be a reciprocal of an integer
    
    speed = 1.0 / 4.0;
}


void Character::preLoop()
{
    // Check if the character has reached his destination
    
    float limit = 1.0f - 0.0001f;
    
    if (moving && (abs(subX) >= limit || abs(subY) >= limit) )
    {
        // Convert sub map position to map position
        
        mapX += directionX[direction];
        mapY += directionY[direction];
        
        subX -= directionX[direction];
        subY -= directionY[direction];
        
        moving = false;
    }
}


void Character::advanceFrame()
{
    if (moving)
    {
        // Move the character's sub-map position a bit
        
        subX += speed * directionX[direction];
        subY += speed * directionY[direction];
    }
    
    // Call parent function
    
    Entity::advanceFrame();
}


void Character::startMoving(int direction)
{
    // Change sprite column
    
    tileX = direction;
    
    int newMapX = mapX + directionX[direction];
    int newMapY = mapY + directionY[direction];
    
    // Check for collisions
    
    if (game->world.isCollision(newMapX, newMapY))
    {
        printf("Collides");
        stopMoving();
    }
    else
    {
        this->direction = direction;
        
        moving = true;
        animationPlay();
    }
}


void Character::stopMoving()
{
    // Quantize the character's position
    
    subX = 0.0f; subY = 0.0f;
    
    // Stop animation
    
    moving = false;
    animationStop();
}


bool Character::isMoving()
{
    return moving;
}











