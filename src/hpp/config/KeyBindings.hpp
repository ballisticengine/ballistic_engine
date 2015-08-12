#ifndef KEYBINDINGS_HPP
#define	KEYBINDINGS_HPP

#include <string>
#include <iostream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost::property_tree;
using boost::property_tree::ptree;


#include "config/path.hpp"
#include "config/keycode_map.hpp"
#include "types/basic_typedefs.hpp"

typedef map<keycode_t, string> key_action_map;

class KeyBindings {
protected:
    FRIEND_TEST(KeyBindings, KeyBindingsTest);
    string bindings_filename;
    ptree pt;
    key_action_map key_actions;
public:
    KeyBindings(string bindings_filename);
    bool loadBindings();
    key_action_map getBindings();
    ~KeyBindings();
};

#endif	

