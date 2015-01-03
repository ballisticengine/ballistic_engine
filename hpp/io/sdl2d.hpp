#ifndef SDL2D_HPP
#define	SDL2D_HPP

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <string>
#include "misc/singleton.hpp"
#include "config/path.hpp"

using namespace std;

class Draw2d : public singleton<Draw2d> {
    protected:
      TTF_Font *font;  
      
    public:
        Draw2d();
        SDL_Surface *surf;
        void setSurface(SDL_Surface *surf);
        void text(string text);
};

#endif	

