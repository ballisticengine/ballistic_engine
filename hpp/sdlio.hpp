#ifndef SDLIO_HPP
#define	SDLIO_HPP

#include <SDL.h>

#include "singleton.hpp"

class sdlIO : public singleton {
    void initWindow();
    sdlIO();
};

#endif 