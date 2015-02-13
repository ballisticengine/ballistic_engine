#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost::property_tree;

#include "factories/factory.hpp"
#include "types/types.hpp"
#include "types/shape.hpp"
#include "loaders/loaderMD2.hpp"
#include "loaders/loaderXML.hpp"
#include "anim/animator.hpp"
#include "anim/modelAnimator.hpp"
#include "misc/utils.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GEOM_MEM_EXT "[geom]"
#define MD2_EXT "md2"
#define XML_EXT "xml"


class shapeFactory: public factory, public singleton<shapeFactory> {
protected:
	virtual void * actualLoad(string fn);
	e_loc scale;
	ptree *shp;
	ModelAnimator *animator;
        virtual string getSubDir();

public:
	virtual void setAnimator(ModelAnimator *a);
	virtual shape * getShape(string fn,bool force_common=false);
        virtual void * get(string fn,bool force_common=false,bool clone=false);
        virtual ModelAnimator * getAnimator();
	virtual void setScale(e_loc scale);
	virtual shape * getXML(ptree shp);
	shapeFactory();
	 
};

#endif