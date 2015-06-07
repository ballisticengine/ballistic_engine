#include "world/World.hpp"

bool World::parseXml(string &fn) {
    cout << "Loading...\n";
    this->observer.name = "observer";
    this->observer.type = "observer";

    string wd = fn, level_path = string(CONFIG_DIR) + string(DS) + string(LVL_DIR) + DS + fn, level_xml = level_path + DS + string("level.xml");
    ;

    cout << "Level: " << level_path << endl;
    ShapeFactory *shapef = (ShapeFactory *) ShapeFactory::getInstance();
    shapef->setLevel(fn);
    TextureFactory *texf = (TextureFactory *) TextureFactory::getInstance();
    texf->setLevel(fn);
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(level_xml, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn = pt.get<string>("world.config.skybox");
    this->sky = new Skybox(skyfn);
    this->observer.current_weapon = Config::getInstance()->available_weapons[pt.get<string>("world.config.default_weapon")];
    ;

    ptree& World_jp = pt.get_child("world.config.jump_point");
    //  e_loc jx,jy,jz,rx,ry,rz;
    e_loc jx = World_jp.get<e_loc>("x"),
            jy = World_jp.get<e_loc>("y"),
            jz = World_jp.get<e_loc>("z"),
            rx = World_jp.get<e_loc>("rx"),
            ry = World_jp.get<e_loc>("ry"),
            rz = World_jp.get<e_loc>("rz");


    try {
        roomrot_x = pt.get<e_loc>("world.config.rotation.x");
        roomrot_y = pt.get<e_loc>("world.config.rotation.y");
        roomrot_z = pt.get<e_loc>("world.config.rotation.z");
    } catch (std::exception e) {
        roomrot_x = roomrot_y = roomrot_z = 0;
    }

    PreloadStore *ps = PreloadStore::getInstance();
    ptree preloads = pt.get_child("world.preloads");

    BOOST_FOREACH(const ptree::value_type &preload, preloads) {
        string name = preload.second.get<string>("name"),
                type = preload.second.get<string>("type"),
                file = preload.second.get<string>("file");
        cout << "File " << file << ", " << name << endl;
        if (type == "model") {
            Shape *shp = shapef->getShape(file);
            ps->shape_preloads[name] = shp;
        } else if (type == "texture") {
            Texture *tex = (Texture *) texf->get(file);
            ps->tex_preloads[name] = tex;
        }

    }



    string gfn = level_path + DS + "geometry.xml";

    /* Geometria poziomu */
    ptree gpt;
    read_xml(gfn, gpt, boost::property_tree::xml_parser::trim_whitespace);
    ptree &rooms = gpt.get_child("level.rooms");

    BOOST_FOREACH(const ptree::value_type &room, rooms) {

        Shape *fs = shapef->getXML((ptree) room.second);

        RoomEntity *roomE = new RoomEntity();
        shapef->setAnimator(&roomE->model_animator);
        //poly_list polys=fs->getPolys();

        roomE->ambient_light.r = room.second.get<e_loc>("ambient_light.r"),
                roomE->ambient_light.b = room.second.get<e_loc>("ambient_light.b"),
                roomE->ambient_light.g = room.second.get<e_loc>("ambient_light.g");

        roomE->name = room.second.get<string>("shape.name");
        cout << "Ambient light: " << roomE->ambient_light.r << ", " << roomE->ambient_light.g << ", " << roomE->ambient_light.b << endl;
        roomE->setModel(fs);
        e_loc
        rx = room.second.get<e_loc>("location.x"),
                ry = room.second.get<e_loc>("location.y"),
                rz = room.second.get<e_loc>("location.z")
                ;
        roomE->locate(rx, ry, rz);
        //roomE->face(roomrot_x, roomrot_y, roomrot_z);
        roomE->calcBoundings();
        this->addRoomEntity(roomE);
       // collisions.addRoom(roomE);
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
                shapef->setScale(sc);
                ModelInfo *mi = (ModelInfo *) shapef->get(entobj.second.get<string>("model"));
                ObjectEntity *oe = new ObjectEntity();
                //shp->calculateNormals(); //UWAGA!!
                oe->no_physics = !physics;
                oe->setModel(mi->s);
                oe->locate(x, y, z);
                if (mi->boundings.size() > 0) {
                    cout << entobj.second.get<string>("model") << " has custom bounding boxes " << endl;
                    for (int i = 0; i < mi->boundings.size(); i++) {
                        cout << mi->boundings[i]->name << endl;
                        //                        mi->boundings[i]->max.x+=x;
                        //                        mi->boundings[i]->max.y+=y;
                        //                        mi->boundings[i]->max.z+=z;
                        //                        mi->boundings[i]->min.x+=x;
                        //                        mi->boundings[i]->min.y+=y;
                        //                        mi->boundings[i]->min.z+=z;
                        oe->addBoundingBox(mi->boundings[i]);
                    }
                    //oe->boundings=mi->boundings;
                    continue;
                } else {
                    oe->addBoundingBox(new BoundingCube(oe->getModel()));
                }
                oe->face(-90, 0, 0); //tymczasowo, i tak wi�kszo�� obiekt�w potrzebuje dok�adnie takiego obrotu
                current_e = (Entity *) oe;
                //oe->face(rx,ry,rz);
                //oe->velocity.t.x=10;
                roomE->addObjectEntity(oe);
                collisions.addEntity((Entity *)oe);
                if (mi->s->frame_count > 0) {
                    roomE->model_animator.addShape(mi->s);
                }
            } else if (type == "light") {
                //cout << "Light " << x << ", " << y << ", " << z << endl ;	
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
            } else if (type == "bounding") {

                e_loc
                minx = entobj.second.get<float>("min.x"),
                        miny = entobj.second.get<float>("min.y"),
                        minz = entobj.second.get<float>("min.z"),
                        maxx = entobj.second.get<float>("max.x"),
                        maxy = entobj.second.get<float>("max.y"),
                        maxz = entobj.second.get<float>("max.z")
                        ;
                cout << "Found bounding\n";
                cout << minx << ", " << miny << ", " << minz << ", " << maxx << ", " << maxy << ", " << maxz << endl;
                BoundingCube *bc = new BoundingCube(minx, miny, minz, maxx, maxy, maxz);
                bc->name = name;
                //roomE->boundings.push_back(bc);
                //roomE->setBoundingBox(bc);
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
    cout << "Jumppoint: " << (long) jx << ", " << (long) jy << ", " << (long) jz << endl;
    observer.setCamera(&default_Camera);
    observer.locate(jx, jy, jz);
    observer.face(rx, ry, rz);
     collisions.addEntity((Entity *)&observer);
    //observer.boundings[0]->rotate(-90,0,0);
    //texf->setWD(COMMON_DIR);
    Texture *stex = (Texture *) texf->get("@car.bmp");
    this->testsprite = new Sprite(stex);
    this->active_room = this->rooms[0];
   // octree=generateOctree(this->rooms);
    return true;
}
