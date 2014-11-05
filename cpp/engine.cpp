#include "engine.hpp"

typedef boost::shared_ptr<world> world_ptr;

int add_five(int x) {
  return x + 5;
}

BOOST_PYTHON_MODULE(Pointless)
{
    def("add_five", add_five);
}

typedef boost::shared_ptr<world> world_ptr;

BOOST_PYTHON_MODULE(world)
{
    class_<world,world_ptr>("world")
        //.def("test", &world::test)
		
    ;
};


void engine::pythonInit() {
	PyScripting::getInstance()->loadManipulators();
	//Py_Initialize();
	// initPointless();
	// initworld();

	// char *pymain_module=Utils::loadText("python/__init__.py");
//	 cout << pymain_module;
	//PyRun_SimpleString(pymain_module);
	

  
	//import("world_py");
//PyRun_SimpleString("pyApi.world_callbacks.test()");
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
