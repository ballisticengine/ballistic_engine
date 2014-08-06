#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "singleton.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, jeœli nie istniej¹ - ³aduje
*/


class factory   {
protected:
	map <string,void *> items;
	vector <void *> item_ptr;
	virtual void * actualLoad(string fn)=0;
public:
	 virtual ~factory();
	 virtual void * get(string fn);
	 virtual vector <void *> getAll();
	
};

#endif