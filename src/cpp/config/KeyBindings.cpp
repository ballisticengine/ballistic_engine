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
        KeybindAction action;
        string key_id = key.second.get<string>("id"),
                key_action = key.second.get<string>("action"),
                action_type = key.second.get<string>("type")
                ;

        keycode_t keycode;

        if (key_id.find("K_") != std::string::npos) {
            keycode = keycode_map[key_id];
            action.key_type = KT_SYM;
        } else if (key_id.size() == 1) {
            //TODO to lower and convert to sym
            keycode = (keycode_t) key_id[0];
            action.key_type = KT_CHAR;

        } else {
            keycode = 0;
            action.key_type = KT_NONE;
        }

        action.name = key_action;

        if (action_type == "KEYPRESS") {
            action.stroke_type = KB_KEYPRESS;
        } else if (action_type == "KEYUP") {
            action.stroke_type = KB_KEYUP;
        } else if (action_type == "KEYDOWN") {
            action.stroke_type = KB_KEYDOWN;
        }

        key_actions[keycode] = action;
    }


    return true;

}

key_action_map KeyBindings::getBindings() {
    return key_actions;
}