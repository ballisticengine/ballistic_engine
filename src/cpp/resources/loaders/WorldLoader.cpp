#include "resources/loaders/WorldLoader.hpp"
#include "world/World.hpp"

using boost::property_tree::ptree;

extensions_s WorldLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("xml");
    return exts;
}

ResourceType WorldLoader::getType() {
    return LEVEL;
}

void *WorldLoader::load(string level_name) {
    World *w = new World();
    
    ptree pt;
    read_xml(level_name, pt, 
            boost::property_tree::xml_parser::trim_whitespace 
            | boost::property_tree::xml_parser::no_comments);
    
    
   
    return (void *)w;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new WorldLoader();
    }
}