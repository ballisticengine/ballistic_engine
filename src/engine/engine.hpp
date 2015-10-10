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
#include "io/sdlio.hpp"
#include "config/Config.hpp"

#include "types/shape.hpp"

#include "misc/utils.hpp"
#include "config/EngineState.hpp"

#include "python/scripting.hpp"
#include "libload/LibLoad.hpp"
#include "renderer/RenderingManager.hpp"
#include "renderer/RendererInterface.hpp"

#include "ui/librocket_interfaces/SystemInterfaceSDL2.hpp"
#include "ui/librocket_interfaces/ShellFileInterface.hpp"



class Engine : public Singleton<Engine> {
    SdlIO *io;
    World *world;
    void pythonInit();
    
public:
    void registerModules();
    void prepare();
    void start();
    ~Engine();
};

#endif	/* ENGINE_HPP */

