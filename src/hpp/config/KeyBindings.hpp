#ifndef KEYBINDINGS_HPP
#define	KEYBINDINGS_HPP

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost::property_tree;
using boost::property_tree::ptree;

#include "config/path.hpp"

class KeyBindings {
protected:
    FRIEND_TEST(KeyBindings, KeyBindingsTest);
    string bindings_filename;
    bool loadBindings();
    ptree pt;
public:
    KeyBindings(string bindings_filename);
    ~KeyBindings();
};

#endif	

