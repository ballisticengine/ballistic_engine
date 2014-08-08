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
    
	r = new rendererGL();
     
    cout << "IO\n";
    
	
	io = new sdlIO(); 
   
	r->setInitWindow(sdlIO::initWindow);
	r->setFlush(sdlIO::flush);
	
	

}

void engine::start() {
    
	boost::thread rt(boost::ref(*r));
	boost::thread it(boost::ref(*io));
	it.join();
	//it.join();
	
	//rt.join();
	//rt.join();
}
