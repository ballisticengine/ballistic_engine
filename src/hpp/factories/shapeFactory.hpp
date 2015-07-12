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
#include "loaders/LoaderXML.hpp"
#include "anim/animator.hpp"
#include "anim/modelAnimator.hpp"
#include "misc/utils.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GEOM_MEM_EXT "[geom]"
#define MD2_EXT "md2"
#define XML_EXT "xml"


class ShapeFactory: public Factory, public Singleton<ShapeFactory> {
protected:
	virtual void * actualLoad(string fn);
	e_loc scale;
	ptree *shp;
	ModelAnimator *animator;
        virtual string getSubDir();

public:
	virtual void setAnimator(ModelAnimator *a);
	virtual Shape * getShape(string fn,bool force_common=false);
        virtual ModelAnimator * getAnimator();
	virtual void setScale(e_loc scale);
	virtual Shape * getXML(ptree shp);
	ShapeFactory();
	 
};

#endif