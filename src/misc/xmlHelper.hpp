#ifndef XML_HELPER_HPP
#define	XML_HELPER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "types/types.hpp"

using namespace boost::property_tree;

ptree makeRotationNode(Coords c);
ptree makeTranslationNode(Coords c);
ptree makeLocationNode(scalar_t x=0, scalar_t y=0, scalar_t z=0);
ptree makeCoordsNode(Coords c);
ptree makeRGBANode(scalar_t r, scalar_t g, scalar_t b, scalar_t a=1);
ptree makeRGBANode(ColorRGBA c);
ptree makeUVNode(scalar_t u, scalar_t v);


#endif	

