#include "engine.hpp"

 void engine::prepare() {
    cout << "Preparing..." << endl;
    cout << "World\n";
    world *w=(world *)world::getInstance();
    w->parseXml("data/level.xml");
    
    cout << "IO\n";
    io=new sdlIO();//(sdlIO *)sdlIO::getInstance();
    io->initWindow();
    
    
 }
 
 void engine::start() {
     io->eventLoop();
 }
