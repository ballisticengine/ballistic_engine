#include "world.hpp"

ent_list world::getEntities() {

}

skybox * world::getSkybox() {
    return this->sky;
}

void world::makeTestWorld() {
    this->sky = new skybox("test_texture.bmp");
}

bool world::parseXml(const string &fn) {
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn= pt.get<string>("world.config.skybox");
    cout << "}"<<skyfn << "}" << endl;
   this->sky = new skybox(skyfn);
}
