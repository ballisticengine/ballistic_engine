#ifndef MODELVIEW_HPP
#define	MODELVIEW_HPP

#include <iostream>

#include "loaders/loaderXML.hpp"
#include "modelview.hpp"
#include "renderer.hpp"

using namespace std;

#include <SDL2/SDL.h>

class ModelView {
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
    static SDL_Window *window;
    static Renderer *r;
    bool exit;
public:
    static void initWindow();
    void eventLoop();
    ModelView();
    ~ModelView();

};

#endif	

