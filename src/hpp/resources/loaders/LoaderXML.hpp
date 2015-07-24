#ifndef LOADER_XML_H
#define LOADER_XML_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <iostream>



using namespace std;
using namespace boost::property_tree;


#include "types/types.hpp"
#include "types/shape.hpp"

#include "types/material.hpp"
#include "types/boundingCube.hpp"
#include "misc/utils.hpp"
#include "resources/Loader.hpp"
#include "resources/ModelInfo.hpp"

class LoaderXML : public Loader {
protected:
    void toShape(ptree &geom,ptree &shape_xml,ModelInfo *mi);
public:
    virtual extensions_s getFileExtensions();
    virtual ResourceType getType();
    virtual void *load(string file_name);
    void *loadFromData(void *data, size_t size);
};
#endif