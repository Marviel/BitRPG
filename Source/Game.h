//
//  Game.h
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Bit_Game_h
#define Bit_Game_h

#include <SDL/SDL.h>
#include "CacheLoader.h"
#include "World.h"
#include "Character.h"


class Game
{
public:
    Game();
    
    int onExecute();
    
    // Actions
    
    bool onInit();
    void checkEvents();
    void checkKeys();
    void preLoop();
    void postLoop();
    void onRender();
    float limitFramerate();
    void onCleanup();
    
    CacheLoader cache;
    World world;
    SDL_Surface* display;
    
    Character player;
    
private:
    bool running;
    float maxFramerate;
    Uint32 lastTicks;
    
};

extern Game* game;

#endif
