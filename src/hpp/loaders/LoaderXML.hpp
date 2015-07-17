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
#include "types/shape.hpp"
#include "factories/textureFactory.hpp"
#include "types/material.hpp"
#include "types/boundingCube.hpp"
#include "misc/utils.hpp"
#include "loaders/Loader.hpp"

struct ModelInfo {
    Shape *s;
    bounding_list boundings;    
};

class LoaderXML : public Singleton<LoaderXML> {
protected:
    bool  force_common;
    //bool loadFile(string fn);
 void toShape(ptree &geom,ptree &shape_xml,ModelInfo *mi);
public:
	string loadXML(ptree &tree,Shape *s);
	bool load(string fn, ModelInfo *mi,bool force_common=false);
	string getName(ptree &tree);
	//loadXML(string fn,shape *s); //TODO
};
#endif