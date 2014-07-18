#include "engine.hpp"

 void engine::prepare() {
    cout << "Preparing..." << endl;
    cout << "World\n";
    world *w=(world *)world::getInstance();
    w->parseXml("data/level.xml");
    
    //na razie tak
    rendererGL *r=(rendererGL *)rendererGL::getInstance();
//    skybox *s=w->getSkybox();
//    texture *t=s->getTexture();
    
    
    
    cout << "IO\n";
    io=new sdlIO();//(sdlIO *)sdlIO::getInstance();
    io->initWindow();
    
    
 }
 
 void engine::start() {
     io->eventLoop();
 }
