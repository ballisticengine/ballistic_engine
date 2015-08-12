#include "config/KeyBindings.hpp"

KeyBindings::KeyBindings(string bindings_filename)
: bindings_filename(bindings_filename) {


}

KeyBindings::~KeyBindings() {
    /////////////
}

bool KeyBindings::loadBindings() {
    read_xml(this->bindings_filename,
            pt,
            boost::property_tree::xml_parser::trim_whitespace);

    ptree keybindings_xml = pt.get_child("keybindings");

    BOOST_FOREACH(const ptree::value_type &key, keybindings_xml) {

        string key_id = key.second.get<string>("id"),
                key_action = key.second.get<string>("action")
                ;

        keycode_t keycode;

        if (key_id.find("K_") != std::string::npos) {
            keycode = keycode_map[key_id];
        } else if (key_id.size() == 1) {
            keycode = (keycode_t) key_id[0];

        } else {
            keycode = 0;
        }
        key_actions[keycode] = key_action;
    }


    return true;

}

action_map KeyBindings::getBindings() {
    return key_actions;
}