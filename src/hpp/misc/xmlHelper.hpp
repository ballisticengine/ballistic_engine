#ifndef XML_HELPER_HPP
#define	XML_HELPER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "types/types.hpp"

using namespace boost::property_tree;

ptree makeLocationNode(e_loc x=0, e_loc y=0, e_loc z=0);
ptree makeRGBANode(e_loc r, e_loc g, e_loc b, e_loc a=1);

#endif	

