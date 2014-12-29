#ifndef LOADER_XML_H
#define LOADER_XML_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <iostream>



using namespace std;
using namespace boost::property_tree;

#include "misc/singleton.hpp"
#include "types/types.hpp"
#include "types/facetexShape.hpp"
#include "factories/textureFactory.hpp"
#include "types/material.hpp"
#include "misc/utils.hpp"

class loaderXML : public singleton<loaderXML> {
protected:
 //bool loadFile(string fn);
 void toShape(ptree &geom,ptree &shape,faceTexShape *s);
public:
	string loadXML(ptree &tree,faceTexShape *s);
	bool load(string fn, faceTexShape *s);
	string getName(ptree &tree);
	//loadXML(string fn,shape *s); //TODO
};
#endif