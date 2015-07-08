#include "python/scripting.hpp"

void PyScripting::loadManipulators() {
	
        vector<string> scripts=Config::getInstance()->getScripts();
        for(int i=0; i<scripts.size(); i++) {
            string pyfn=string(CONFIG_DIR)+DS+string(COMMON_DIR)+DS+
                       string("python")+DS+scripts[i]+".py";
            cout << "Global python script: " << pyfn << endl;
            PyManipulator *pyman=new PyManipulator(pyfn);
			manipulators.push_back(pyman);
        }
	broadcast("Init",0);
	broadcast("SelfLoad",0);
}

PyScripting::PyScripting() {
	Py_Initialize();
	PyEval_InitThreads(); 
	init_world();
        init_hud(); 
        init_timer();
        init_engine();
       
}

PyScripting::~PyScripting() {
	Py_Finalize();
}


void PyScripting::broadcast(string name,void *paramA,void *paramB,void* paramC,void* paramD) {
    
    
    while(!m.try_lock()) {} ;
    
    for(int i=0; i<manipulators.size(); i++) {
		manipulators[i]->signal(name,paramA,paramB,paramC,paramD); 
	}
    m.unlock();
}

