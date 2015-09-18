#include "resources/WorldLoader.hpp"
#include "world/World.hpp"
#include "types/skybox.hpp"

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

    string skyfn = pt.get<string>("level.config.skybox");
    Ballistic::Types::Texture *sky_texture;
    this->addDependency(skyfn, (void **) &sky_texture);
    w->sky = new Skybox(sky_texture);

    ptree& jump_point = pt.get_child("level.config.jump_point");

    e_loc jx = jump_point.get<e_loc>("x"),
            jy = jump_point.get<e_loc>("y"),
            jz = jump_point.get<e_loc>("z"),
            rx = jump_point.get<e_loc>("rx"),
            ry = jump_point.get<e_loc>("ry"),
            rz = jump_point.get<e_loc>("rz");

    


    //ptree &rooms = gpt.get_child("level.rooms");
    
    return (void *) w;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new WorldLoader();
    }
}