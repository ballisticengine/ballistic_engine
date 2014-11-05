#include "python.hpp"


PyManipulator::PyManipulator(string file) {
 code=Utils::loadText(file);
 filename=boost::filesystem::basename(file);
 PyRun_SimpleString(code);
 boost::filesystem::path p(filename);
 classname=p.stem().string();
 iname=classname+"_instance";
 string codeinit=iname+"="+classname+"()";

 cout << "INIT: " << codeinit << endl;
 PyRun_SimpleString(codeinit.c_str());
 cout << "Loaded python script " << filename << endl;
}

void PyManipulator::signal(string name,void *params) {
	string sigcode=iname+".on"+name+"()";
	cout << "Signal " << sigcode << endl;
	PyRun_SimpleString(sigcode.c_str());
}

PyManipulator::~PyManipulator() {
 delete code;
}


//////////////////

void PyScripting::loadManipulators() {
	namespace fs = boost::filesystem;
	fs::path py_dir("python/manipulators/");
	fs::directory_iterator end_iter;
	for( fs::directory_iterator dir_iter(py_dir) ; dir_iter != end_iter ; ++dir_iter) {
		if (fs::is_regular_file(dir_iter->status()) ) {
			PyManipulator *pyman=new PyManipulator(dir_iter->path().string());
			manipulators.push_back(pyman);
		}
	}

	broadcast("SelfLoad",0);
}

PyScripting::PyScripting() {
	Py_Initialize();
}

PyScripting::~PyScripting() {
	Py_Finalize();
}


void PyScripting::broadcast(string name,void *params) {
	for(int i=0; i<manipulators.size(); i++) {
		manipulators[i]->signal(name,params);
	}
}