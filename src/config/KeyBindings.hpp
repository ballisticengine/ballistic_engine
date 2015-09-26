#ifndef KEYBINDINGS_HPP
#define	KEYBINDINGS_HPP

#include <string>
#include <iostream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;
using namespace boost::property_tree;
using boost::property_tree::ptree;


#include "config/path.hpp"
#include "config/keycode_map.hpp"
#include "types/basic_typedefs.hpp"

typedef map<string, string> kb_param_t;

enum KeyBindType {
    KB_KEYUP,
    KB_KEYDOWN,
    KB_KEYPRESS
};

enum KeyType {
    KT_CHAR,
    KT_SYM,
    KT_NONE
};

struct KeybindAction {
    string name;
    KeyBindType stroke_type;
    kb_param_t params;
    KeyType key_type;
};

typedef map<keycode_t, KeybindAction> key_action_map; //TODO: set

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

