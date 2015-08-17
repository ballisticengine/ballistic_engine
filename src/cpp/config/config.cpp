#include <bits/stl_pair.h>

#include "config/Config.hpp"

void Config::loadWeapons() {

}

string Config::getRenderer() {
    return pt.get<string>("config.screen.renderer.name");

}

Config::Config() {

    string fn = string(CONFIG_DIR) + string(DS) + string(CONFIG_FN);

    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);

    vd.width = pt.get<int>("config.screen.resx");
    vd.height = pt.get<int>("config.screen.resy");
    vd.frustum_start = pt.get<float>("config.screen.frustum_start");
    vd.frustum_end = pt.get<float>("config.screen.frustum_end");
    vd.frustum_x = pt.get<float>("config.screen.frustum_width");
    vd.frustum_y = pt.get<float>("config.screen.frustum_height");


    EngineState::getInstance()->setBool("fullscreen", pt.get<bool>("config.screen.fullscreen"));
    EngineState::getInstance()->setBool("desktop_fs", pt.get<bool>("config.screen.use_desktop_fs"));

    string keybindings_file = string(CONFIG_DIR) + string(DS)
            + pt.get<string>("config.keybindings");


    start_level = pt.get<string>("config.game.start_level");
    ptree scripts_xml = pt.get_child("config.scripts");

    BOOST_FOREACH(const ptree::value_type &script, scripts_xml) {
        string script_s = script.second.get_value<string>();
        scripts.push_back(script_s);
    }

    HUD *hud = HUD::getInstance();
    ptree hud_xml = pt.get_child("config.screen.hud");

    BOOST_FOREACH(const ptree::value_type &image, hud_xml) {
        string
        name = image.second.get<string>("name"),
                texname = image.second.get<string>("texture")
                ;
        e_loc
        width = image.second.get<e_loc>("width"),
                height = image.second.get<e_loc>("height"),
                x = image.second.get<e_loc>("x"),
                y = image.second.get<e_loc>("y")
                ;

        hud->addImage(texname, name, width, height, x, y);

    }

    cout << "Loading weapons: \n";
    ptree weapons_xml = pt.get_child("config.game.weapons");
    Weapon *prev = 0;

    BOOST_FOREACH(const ptree::value_type &weapon_xml, weapons_xml) {
        Weapon *w = new Weapon();
        w->name = weapon_xml.second.get<string>("name");
        w->display_name = weapon_xml.second.get<string>("display_name");
        w->initial_velocity = weapon_xml.second.get<e_loc>("velocity");
        w->model = new UiMesh(weapon_xml.second.get<string>("model"), 0, 0, -10);
        w->model->c.translation.x = weapon_xml.second.get<e_loc>("location.x");
        w->model->c.translation.y = weapon_xml.second.get<e_loc>("location.y");
        w->model->c.translation.z = weapon_xml.second.get<e_loc>("location.z");
        w->model->c.rotation.x = weapon_xml.second.get<e_loc>("rotation.x");
        w->model->c.rotation.y = weapon_xml.second.get<e_loc>("rotation.y");
        w->model->c.rotation.z = weapon_xml.second.get<e_loc>("rotation.z");
        w->model->scale = weapon_xml.second.get<e_loc>("scale");
        w->bullet = (Shape *) ResourceManager::getInstance()->get(weapon_xml.second.get<string>("bullet"));
        w->decal = (Ballistic::Types::Texture *) ResourceManager::getInstance()->get(weapon_xml.second.get<string>("decal.texture"));
        w->prev = prev;
        w->next = 0;
        if (prev) {
            prev->next = w;
        }
        prev = w;
        available_weapons[w->name] = w;
        cout << w->display_name << endl;
    }
    KeyBindings *kb = new KeyBindings(keybindings_file);
    kb->loadBindings();
    this->setKeyBindings(kb);
}

VideoData * Config::getVD() {
    return &vd;
}

string & Config::getStart() {
    return start_level;
}

ptree & Config::getNode(string node) {
    return pt.get_child(node);
}

const ptree & Config::getPtree() {
    return this->pt;
}

vector <string> Config::getScripts() {
    return this->scripts;
}

KeyBindings * Config::getKeyBindings() {
    return this->key_bindings;
}

void Config::setKeyBindings(KeyBindings *key_bindings) {
    this->key_bindings = key_bindings;
}