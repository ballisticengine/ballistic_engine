#ifndef LOADER_XML_H
#define LOADER_XML_H

#include <string>

using namespace std;

#include "singleton.hpp"
#include "types.hpp"

class loaderXML : public singleton<loaderXML> {
protected:
 string xml;
 //bool loadFile(string fn);
 shape * toShape();
public:
	bool loadXMLStr(string xml,shape *s);
	//loadXMLFile(string fn,shape *s); //TODO
};
#endif