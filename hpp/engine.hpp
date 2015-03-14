/* 
 * File:   engine.hpp
 * Author: maciek
 *
 * Created on July 15, 2014, 7:53 PM
 */

#ifndef ENGINE_HPP
#define	ENGINE_HPP

#include <iostream>
#include <string>

#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>

using namespace boost::python;

using namespace std;

#include "misc/singleton.hpp"
#include "world/World.hpp"
#include "renderer/GL/RendererGL.hpp"
#include "renderer/GL/GLPreview.hpp"
#include "io/sdlio.hpp"
#include "config/Config.hpp"
#include "factories/shapeFactory.hpp"
#include "types/shape.hpp"

#include "misc/utils.hpp"

#include "python/scripting.hpp"
#include "libload/LibLoad.hpp"

typedef boost::shared_ptr<World> World_ptr;

class Engine : public Singleton<Engine> {
    SdlIO *io;
    RendererAbstract *r;
public:
    void pythonInit();
    void prepare();
    void preview(string model);
    void start();
    ~Engine();
};

#endif	/* ENGINE_HPP */

