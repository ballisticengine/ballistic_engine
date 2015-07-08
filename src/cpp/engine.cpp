/*
 TODO: engine state switching
 * States: normal - edit
 * In edit S saves current level to file
 */
#include "engine.hpp"

void Engine::pythonInit() {
    PyScripting::getInstance()->loadManipulators();

}

void Engine::prepare() {
    cout << "Preparing..." << endl;
 
    cout << "Config init..." << endl;
    Config::getInstance();
    
    EngineState::getInstance()->setBool("exit", false);
    EngineState::getInstance()->setBool("edit_mode", false);
    EngineState::getInstance()->setBool("debug_visual", false);
    EngineState::getInstance()->setBool("lighting", true);
    EngineState::getInstance()->setBool("noclip", false);
    EngineState::getInstance()->setBool("fullscreen", false);
    EngineState::getInstance()->setBool("desktop_fs", false);
    EngineState::getInstance()->setBool("light", false);
    EngineState::getInstance()->setString("version", "Staging");
    
    cout << "Loading world...\n";
    World *w = (World *) World::getInstance();
    string start_lvl_dir = string(CONFIG_DIR) + string(DS) + string(LVL_DIR),
            start_lvl = start_lvl_dir + DS + Config::getInstance()->getStart();
    cout << start_lvl << endl;
    w->parseXml(Config::getInstance()->getStart());

    VideoData vd = *Config::getInstance()->getVD();

    r = LibLoad::getInstance()->getRenderer(Config::getInstance()->getRenderer());
    
    cout << "IO\n";
    

    io = new SdlIO();

    io->initWindow(io);
    io->setRenderer(r);

    cout << "Renderer init\n";
    r->init();
    cout << "Camera set\n";
    r->setCamera(w->getCurrentCamera());
    cout << "Flush set\n";
    r->setFlush(SdlIO::flush);
    
    this->pythonInit();
    cout << "World loop\n";
    boost::thread(boost::ref(*w));
//         cout << "Renderer loop\n";
//    boost::thread(boost::ref(*r));

}

Engine::~Engine() {

}

void Engine::start() {
   
    boost::thread(boost::bind(&SdlIO::inputThread, SdlIO::getInstance()));

    io->eventLoop();

}
