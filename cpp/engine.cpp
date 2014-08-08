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
	
	videoData vd=*config::getInstance()->getVD();	
    
	r = (rendererGL *) new rendererGL();
     
    cout << "IO\n";
    
	
	io = new sdlIO(); 
	io->initWindow();
	//r->setInitWindow(sdlIO::initWindow);
	r->setFlush(sdlIO::flush);
	
	

}

void engine::start() {
    
	
	//it.join();
	
	//rt.join();
	//rt.join();
}
