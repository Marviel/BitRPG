//
//  main.cpp
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#include "Game.h"
#include <assert.h>


// The ONLY global
Game* game = NULL;


int SDL_main(int argc, char* argv[])
{
    game = new Game();
    
    return game->onExecute();
}


Game::Game()
{
    display = NULL;
    
    running = true;
    maxFramerate = 0.0;
    lastTicks = 0;
}


int Game::onExecute()
{
    // Initialize
    
    if (!onInit()) return -1;
    
    while (running) {
        
        preLoop();
        
        // Query for events
        
        checkEvents();
        
        // Loop through stuff
        
        postLoop();
        
        // Render scene
        
        onRender();
    }
    
    // Clean stuff up
    
    onCleanup();
    
    return 0;
}


bool Game::onInit()
{
    // Initialize scripting language
    
    
    
    
    
    // Initialize all SDL modules
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    // Set up main display window
    
    int width = 640;
    int height = 480;
    int bitDepth = 32;
    Uint32 displayFlags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    
    display = SDL_SetVideoMode(width, height, bitDepth, displayFlags);
    assert(display != NULL);
    
    SDL_WM_SetCaption("Bit", "Bit");
    
    // Initialize map
    
    world.loadMap("map.json");
    
    // Load images
    
    SDL_Surface* playerSurface = cache.loadFile("player.png");
    
    player.setSurface(playerSurface, 32, 32, 0, 0, -7, -11);
    player.setAnimationFormat(1, 4);
    player.setFrameRepeat(4);
    player.mapX = 8;
    player.mapY = 8;
    
    // Set clock
    
    lastTicks = SDL_GetTicks();
    maxFramerate = 30.0f;
    
    return true;
}


void Game::preLoop()
{
    limitFramerate();
    
    player.preLoop();
}


void Game::postLoop()
{
    player.advanceFrame();
}


void Game::onRender()
{
    // Clear buffer
    
    Uint32 background = 0x00000000;
    SDL_FillRect(display, NULL, background);
    
    // Draw map
    
    world.draw(display);
    
    // Draw entities
    
    player.draw(display);
    
    // Flip the double buffer
    
    SDL_Flip(display);
}


float Game::limitFramerate()
{
    // Calculate time since last frame
    
    Uint32 newTicks = SDL_GetTicks();
    int delayTime = 1000.f / maxFramerate - (float) (newTicks - lastTicks);
    
    // Delay to achieve the maxFramerate target
    
    if (delayTime > 0)
    {
        SDL_Delay(delayTime);
    }
    
    // Calculate framerate
    
    newTicks = SDL_GetTicks();
    float framerate = 1000.f / (newTicks - lastTicks);
    lastTicks = newTicks;
    
    return framerate;
}


void Game::onCleanup()
{
    SDL_FreeSurface(display);
    
    SDL_Quit();
}

