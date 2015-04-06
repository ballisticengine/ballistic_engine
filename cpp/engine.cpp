#include "engine.hpp"

void Engine::pythonInit() {
    PyScripting::getInstance()->loadManipulators();

}

void Engine::prepare() {
    cout << "Preparing..." << endl;
 
    cout << "Config init..." << endl;
    Config::getInstance();
   
    cout << "Loading world...\n";
    World *w = (World *) World::getInstance();
    string start_lvl_dir = string(CONFIG_DIR) + string(DS) + string(LVL_DIR),
            start_lvl = start_lvl_dir + DS + Config::getInstance()->getStart();
    cout << start_lvl << endl;
    w->parseXml(Config::getInstance()->getStart());

    VideoData vd = *Config::getInstance()->getVD();

    r = LibLoad::getInstance()->getRenderer(Config::getInstance()->getRenderer());//RendererGL::getInstance();
    
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
