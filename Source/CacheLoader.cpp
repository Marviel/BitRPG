//
//  CacheLoader.cpp
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "CacheLoader.h"
#include <assert.h>


CacheLoader::CacheLoader()
{
    path = "";
    
    int flags = IMG_INIT_PNG;
    int init = IMG_Init(flags);
    
    // PNG library didn't load properly. Inform the user that without
    // graphics, the game will be incredibly lame.
    assert(init == flags);
}

CacheLoader::~CacheLoader()
{
    IMG_Quit();
}


SDL_Surface* CacheLoader::loadFile(const char* filename, bool alpha)
{
    // Check fileCache for existing surface with a similar filename
    
    std::map<const char*, SDL_Surface*>::iterator cacheIterator;
    cacheIterator = fileCache.find(filename);
    
    if (cacheIterator != fileCache.end())
    {
        // Found in cache. Return surface.
        
        return cacheIterator->second;
    }
    else
    {
        // We didn't find it in the cache, so load it from the file.
        
        std::string filepath = path + filename;
        
        SDL_Surface* imageSurface = IMG_Load(filepath.data());
        
        // Check if file loaded properly
        
        assert(imageSurface != NULL);
        
        // Convert image to display format and remove the old one
        
        SDL_Surface *displaySurface;
        
        if (alpha)
            displaySurface = SDL_DisplayFormatAlpha(imageSurface);
        else
            displaySurface = SDL_DisplayFormat(imageSurface);
        
        SDL_FreeSurface(imageSurface);
        
        // Store into fileCache and return the surface
        
        fileCache[filename] = displaySurface;
        return displaySurface;
    }
}

