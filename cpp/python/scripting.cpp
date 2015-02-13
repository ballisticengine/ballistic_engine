#include "python/scripting.hpp"

void PyScripting::loadManipulators() {
	/*namespace fs = boost::filesystem;
	fs::path py_dir("./python/manipulators/");
	fs::directory_iterator end_iter;
	for( fs::directory_iterator dir_iter(py_dir) ; dir_iter != end_iter ; ++dir_iter) {
		if (fs::is_regular_file(dir_iter->status()) ) {
		cout << "Python file: " << dir_iter->path().string() << endl;	
                    PyManipulator *pyman=new PyManipulator(dir_iter->path().string());
			manipulators.push_back(pyman);
		}
                
	}*/
        vector<string> scripts=config::getInstance()->getScripts();
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
       
}

PyScripting::~PyScripting() {
	Py_Finalize();
}


void PyScripting::broadcast(string name,void *paramA,void *paramB,void* paramC,void* paramD) {
    
    
    
    for(int i=0; i<manipulators.size(); i++) {
		manipulators[i]->signal(name,paramA,paramB,paramC,paramD);
	}

}

