#ifndef SDL2D_HPP
#define	SDL2D_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "misc/singleton.hpp"
#include "config/path.hpp"

using namespace std;

class TTF : public Singleton<TTF> {
public:
    TTF_Font *font;
    TTF();
    SDL_Surface *surf;
    void setSurface(SDL_Surface *surf);
    void text(string text);
};

#endif	

