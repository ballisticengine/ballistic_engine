#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost::property_tree;

#include "factory.hpp"
#include "types.hpp"
#include "facetexShape.hpp"
#include "loaderMD2.hpp"
#include "loaderXML.hpp"


#define GEOM_MEM_EXT "[geom]"
#define MD2_EXT "md2"
#define XML_EXT "xml"





class shapeFactory: public factory, public singleton<shapeFactory> {
protected:
	virtual void * actualLoad(string fn);
	e_loc scale;
	ptree *shp;
public:
	virtual void setScale(e_loc scale);
	virtual faceTexShape * getXML(ptree &shp);
	shapeFactory();
	 
};

#endif