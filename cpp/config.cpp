#include "config.hpp"

config::config() {
    string fn=string(CONFIG_DIR)+string(DS)+string(CONFIG_FN);
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
}
        
