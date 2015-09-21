#include "resources/loaders/XMLWorldLoader.hpp"
#include "world/World.hpp"
#include "types/skybox.hpp"
#include "resources/ResourceManager.hpp"
#include "libload/LibLoad.hpp"

using boost::property_tree::ptree;

extensions_s XMLWorldLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("xml");
    return exts;
}

XMLWorldLoader::XMLWorldLoader() {
    
}

void *XMLWorldLoader::load(string level_name) {
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




    ptree &rooms = pt.get_child("level.rooms");
    Loader *xml_loader = LibLoad::getInstance()->getLoaderByExtension("xml", SHAPE);
    ResourceManager *resman = ResourceManager::getInstance();

    BOOST_FOREACH(const ptree::value_type &room, rooms) {
        ptree room_p = (ptree) room.second;
        Shape *room_shape = (Shape *) xml_loader->loadFromData((void *) &room.second, 0);
        resman->resolveAllDependencies();
        RoomEntity *roomE = new RoomEntity();


        roomE->ambient_light.r = room.second.get<e_loc>("ambient_light.r"),
                roomE->ambient_light.b = room.second.get<e_loc>("ambient_light.b"),
                roomE->ambient_light.g = room.second.get<e_loc>("ambient_light.g");

        roomE->name = room.second.get<string>("shape.name");
        roomE->setModel(room_shape);
        e_loc
        rx = room.second.get<e_loc>("location.x"),
                ry = room.second.get<e_loc>("location.y"),
                rz = room.second.get<e_loc>("location.z")
                ;
        roomE->locate(rx, ry, rz);

        roomE->calcBoundings();
        w->addRoomEntity(roomE);
        w->getPhysics()->addRoom(roomE); //TODO
        ptree room_ents = (ptree) room.second.get_child("entities");

        BOOST_FOREACH(const ptree::value_type &entobj, room_ents) {
            string type = entobj.second.get<string>("type"), name = entobj.second.get<string>("name");
            e_loc x = entobj.second.get<float>("location.x"), y = entobj.second.get<float>("location.y"),
                    z = entobj.second.get<float>("location.z"), rx = entobj.second.get<float>("facing.x"),
                    ry = entobj.second.get<float>("facing.y"), rz = entobj.second.get<float>("facing.z");
            Entity *current_e = 0;
            boost::algorithm::to_lower(type);

            if (type == "object") {
                string objectbraces = "[OBJECT]";
                name = name.replace(name.find(objectbraces), objectbraces.length(), "");
                e_loc sc = entobj.second.get<e_loc>("scale");
                bool physics = entobj.second.get<bool>("physics");
                //shapef->setScale(sc);
                Shape *mshape = (Shape *) resman->get(entobj.second.get<string>("model"), SHAPE);
                ObjectEntity *oe = new ObjectEntity();
                //shp->calculateNormals(); //UWAGA!!
                oe->no_physics = !physics;
                oe->setModel(mshape);
                oe->locate(x, y, z);

                oe->addBoundingBox(new BoundingCube(oe->getModel()));

                oe->face(-90, 0, 0); //tymczasowo, i tak wi�kszo�� obiekt�w potrzebuje dok�adnie takiego obrotu
                current_e = (Entity *) oe;
                //oe->face(rx,ry,rz);
                oe->parent = (Entity *) roomE;
                roomE->addObjectEntity(oe);
                w->getPhysics()->addEntity((Entity *) oe); 
                //                if (mi->s->frame_count > 0) {
                //                    roomE->model_animator.addShape(mi->s);
                //                }
            } else if (type == "light") {
                PointLight *l = new PointLight();
                //l->face(-90, 0, 0);
                l->locate(x, y, z);
                ColorRGBA color;
                color.r = entobj.second.get<float>("r");
                color.g = entobj.second.get<float>("g");
                color.b = entobj.second.get<float>("b");
                color.a = 1.0f;
                current_e = (Entity *) l;
                l->setAllColors(color);
                roomE->addLightEntity(l);
            } else if (type == "JumpPoint") {
                //                            jx=x;
                //                            jy=-y;
                //                            jz=z;
                //                            rx=0;
                //                            ry=0;
                //                            rz=0;
            }
            if (current_e) {

                current_e->name = name;
                current_e->type = type;
            }

        }

    }
    
    w->observer.setCamera(&w->default_Camera);
    w->observer.locate(jx, jy, jz);
    w->observer.face(rx, ry, rz);
    w->getPhysics()->addEntity((Entity *) & w->observer);
    
//    Ballistic::Types::Texture *stex = (Ballistic::Types::Texture *) resman->get("@car.bmp"); //??
//    
//    this->testsprite = new Sprite(stex);
    w->active_room = w->rooms[0];
    
    cout << "Loaded world" << endl;
    
    return (void *) w;
}

extern "C" {

    WorldLoader * returnLoader() {
        return (WorldLoader *) new XMLWorldLoader();
    }
}