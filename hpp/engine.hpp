/* 
 * File:   engine.hpp
 * Author: maciek
 *
 * Created on July 15, 2014, 7:53 PM
 */

#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include <iostream>
#include <boost/thread/thread.hpp>

#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>

using namespace boost::python;

using namespace std;

#include "singleton.hpp"
#include "world.hpp"
#include "RendererGL.hpp"
#include "sdlio.hpp"
#include "sdlControls.hpp"
#include "config.hpp"

#include "utils.hpp"

#include "python.hpp"

typedef boost::shared_ptr<world> world_ptr;



class engine : public singleton<engine> {
    sdlIO *io;
	RendererGL *r;
	
    public:
		void pythonInit();
		void prepare();
        void start();
		~engine();
};

#endif	/* ENGINE_HPP */

