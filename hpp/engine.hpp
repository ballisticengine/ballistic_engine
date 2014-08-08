/* 
 * File:   engine.hpp
 * Author: maciek
 *
 * Created on July 15, 2014, 7:53 PM
 */

#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include <iostream>

using namespace std;

#include "singleton.hpp"
#include "world.hpp"
#include "rendererGL.hpp"
#include "sdlio.hpp"
#include "config.hpp"


class engine : public singleton<engine> {
    sdlIO *io;
	rendererGL *r;
    public:
        void prepare();
        void start();
};

#endif	/* ENGINE_HPP */

