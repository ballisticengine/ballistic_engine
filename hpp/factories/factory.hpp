#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "misc/singleton.hpp"
#include "config/path.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/


class factory   {
protected:
	string wd,lvl;
	map <string,void *> items;
	vector <void *> item_ptr;
	bool force_common,uses_common;
        virtual void * actualLoad(string fn)=0;
        virtual string getSubDir()=0;
public:
	 factory();
	 virtual ~factory();
	 virtual void * get(string fn,bool force_common=false);
	 virtual vector <void *> getAll();
	 virtual void setWD(string wd);
         virtual void setLevel(string lvl);
	
};

#endif