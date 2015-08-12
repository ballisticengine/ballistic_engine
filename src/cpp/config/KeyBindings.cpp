#include "config/KeyBindings.hpp"


KeyBindings::KeyBindings(string bindings_filename) {
    //TODO: do not append dirs
    this->bindings_filename=string(CONFIG_DIR) + string(DS) + bindings_filename;
    this->loadBindings();
}


KeyBindings::~KeyBindings() {
    
}

bool KeyBindings::loadBindings() {
     read_xml(this->bindings_filename, 
             pt,
             boost::property_tree::xml_parser::trim_whitespace);
     
     ptree keybindings_xml = pt.get_child("keybindings");
     
     BOOST_FOREACH(const ptree::value_type &key, keybindings_xml) {
         //script.second.get_value<string>(
         cout <<  key.second.get<string>("id") << endl 
                 << key.second.get<string>("action")
                 << endl
                 ;
         
     }

}
