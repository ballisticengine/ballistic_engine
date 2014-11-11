#include "engine.hpp"


void engine::pythonInit() {
	PyScripting::getInstance()->loadManipulators();
	
}

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
    
	
	r=rendererGL::getInstance(); 
    cout << "IO\n";
    
	
	io = new sdlIO(); 
   
	io->initWindow();
	io->setRenderer(r);
	r->init();
	r->setCamera(w->getCurrentCamera());
	r->setFlush(sdlIO::flush);
	
	this->pythonInit();
	
	boost::thread(boost::ref(*w));

	
	

}

engine::~engine() {
  
}

void engine::start() {
	io->eventLoop();
	
}
