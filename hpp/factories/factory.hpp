#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "misc/singleton.hpp"
#include "config/config.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/


class factory   {
protected:
	string wd,lvl;
	map <string,void *> items;
	vector <void *> item_ptr;
	virtual void * actualLoad(string fn)=0;
	static string getExt(string fn);
        virtual string getSubDir()=0;
public:
	 factory();
	 virtual ~factory();
	 virtual void * get(string fn);
	 virtual vector <void *> getAll();
	 virtual void setWD(string wd);
         virtual void setLevel(string lvl);
	
};

#endif