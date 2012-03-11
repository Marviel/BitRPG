//
//  CacheLoader.h
//  Bit
//
//  Created by Andrew Belt on 2/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Bit_CacheLoader_h
#define Bit_CacheLoader_h

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <map>
#include <string>


class CacheLoader
{
public:
    CacheLoader();
    ~CacheLoader();
    
    /**
     * Loads an image from a file and returns a surface
     *
     * @param filename Absolute or relative path to image file
     *
     * Feel free to call this as often as you need it. It returns previously loaded surfaces if found in the cache.
     */
    SDL_Surface* loadFile(const char* filename, bool alpha = true);
    
    bool remove(const char* name);
    
private:
    std::map<const char*, SDL_Surface*> fileCache;
    
    std::string path;
};

#endif
