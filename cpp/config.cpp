#include "config.hpp"

config::config() {
   
    string fn=string(CONFIG_DIR)+string(DS)+string(CONFIG_FN);
    string to_cfg[]={"screen","game"};
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    cout << to_cfg[0] << endl;
    for(int i=0; i<sizeof(to_cfg); i++) {
        cout << to_cfg[i] << endl;
        ptree& entities = pt.get_child(to_cfg[i]);
        BOOST_FOREACH(const ptree::value_type &v, entities) {
              cout << v.first << endl;
        }
    }
    cout.flush();
}
        
