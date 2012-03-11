//
//  Game_onEvent.cpp
//  Bit
//
//  Created by Andrew Belt on 3/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Game.h"
#include <assert.h>


void Game::checkEvents()
{
    SDL_Event event;
    
    // Loop through each event
    
    while (SDL_PollEvent(&event))
    {
        // Quit event
        
        if (event.type == SDL_QUIT)
        {
            running = false;
            return;
        }
        
        // Keyboard event
        
        if (event.type == SDL_KEYDOWN)
        {
            SDLKey key = event.key.keysym.sym;
            
            if (key == SDLK_ESCAPE || key == SDLK_q)
            {
                running = false;
            }
        }
        
        // Mouse event
    }
    
    checkKeys();
}


void Game::checkKeys()
{
    // This checks whether certain keys are pressed, rather than handling
    // one-time keypress events
    
    Uint8* keys = SDL_GetKeyState(NULL);
    
    if (!player.isMoving())
    {
        int direction = -1;
        
        if (keys[SDLK_UP])      direction = 0;
        if (keys[SDLK_RIGHT])   direction = 1;
        if (keys[SDLK_DOWN])    direction = 2;
        if (keys[SDLK_LEFT])    direction = 3;
        
        if (direction != -1)
            player.startMoving(direction);
        else
            player.stopMoving();
        
        
        // Easter egg!
        
        if (keys[SDLK_SPACE])   assert(false);
    }
}



