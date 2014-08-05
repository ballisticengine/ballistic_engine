#include "engine.hpp"

void engine::prepare() {
    cout << "Preparing..." << endl;
    
    cout << "Config init..." << endl;
    config::getInstance();
    
    cout << "World\n";
    world *w = (world *) world::getInstance();
	string start_lvl_dir=string(CONFIG_DIR)+string(DS)+string(LVL_DIR),
		start_lvl=start_lvl_dir+DS+config::getInstance()->getStart();
	cout << start_lvl << endl;
	w->parseXml(start_lvl);  
	
    rendererGL *r = new rendererGL();

      skybox *s=w->getSkybox();
     texture *t=s->getTexture();

    videoData vd;
    vd.width = 640;
    vd.height = 480;
    vd.bpp = 32;
    // 
    cout << "IO\n";
    io = new sdlIO(); //(sdlIO *)sdlIO::getInstance();
    io->initWindow(vd, r);


}

void engine::start() {
    io->eventLoop();
}
