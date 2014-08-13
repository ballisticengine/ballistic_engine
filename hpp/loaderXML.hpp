#ifndef LOADER_XML_H
#define LOADER_XML_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <string>



using namespace std;
using namespace boost::property_tree;

#include "singleton.hpp"
#include "types.hpp"


class loaderXML : public singleton<loaderXML> {
protected:
 
 //bool loadFile(string fn);
 void toShape(ptree &geom,shape *s);
public:
	string loadXML(ptree &tree,shape *s);
	string getName(ptree &tree);
	string getTexFN(ptree &tree);
	//loadXML(string fn,shape *s); //TODO
};
#endif