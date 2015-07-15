#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "misc/singleton.hpp"
#include "config/path.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/


class Factory   {
protected:
	string wd,lvl;
	map <string,void *> items;
	vector <void *> item_ptr;
	bool force_common,uses_common;
        virtual void * actualLoad(string fn, string orig_fn)=0;
        virtual string getSubDir()=0;
        static void abort(string reason="");
public:
	 Factory();
	 virtual ~Factory();
	 virtual void * get(string fn,bool force_common=false,bool clone=false);
	 virtual vector <void *> getAll();
	 virtual void setWD(string wd);
         virtual void setLevel(string lvl);
	
};

#endif