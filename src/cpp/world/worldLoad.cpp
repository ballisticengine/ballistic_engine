#include "world/World.hpp"

bool World::parseXml(string &fn) {

    cout << "Loading...\n";
    this->observer.name = "observer";
    this->observer.type = "observer";

    string wd = fn, level_path = string(CONFIG_DIR) + string(DS) + string(LVL_DIR) + DS + fn, level_xml = level_path + DS + string("level.xml");
    ;

    cout << "Level: " << level_path << endl;
    //ShapeFactory *shapef = (ShapeFactory *) ShapeFactory::getInstance();
    ResourceManager *resman = ResourceManager::getInstance();
    resman->setWD("./data");
    resman->setLevel(fn);

    using boost::property_tree::ptree;
    ptree pt;
    read_xml(level_xml, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn = pt.get<string>("world.config.skybox");

    this->sky = new Skybox((Ballistic::Types::Texture *) resman->get(skyfn));
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
            Shape *shp = (Shape *) resman->get(file);
            ps->shape_preloads[name] = shp;
        } else if (type == "texture") {
            Ballistic::Types::Texture *tex = (Ballistic::Types::Texture *) resman->get(file);
            ps->tex_preloads[name] = tex;
        }

    }



    string gfn = level_path + DS + "geometry.xml";

    /* Geometria poziomu */
    ptree gpt;
    read_xml(gfn, gpt, boost::property_tree::xml_parser::trim_whitespace);
    ptree &rooms = gpt.get_child("level.rooms");
    Loader *xml_loader = LibLoad::getInstance()->getLoaderByExtension("xml");

    BOOST_FOREACH(const ptree::value_type &room, rooms) {

        //Shape *fs = shapef->getXML((ptree) room.second);
        ptree room_p = (ptree) room.second;
        Shape *room_shape = (Shape *) xml_loader->loadFromData((void *) &room.second, 0);
        resman->resolveAllDependencies();
        RoomEntity *roomE = new RoomEntity();

        // shapef->setAnimator(&roomE->model_animator);
        //poly_list polys=fs->getPolys();

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
        //collisions.setWorldTransform(Vector3d(rx,ry,rz));
        //roomE->face(roomrot_x, roomrot_y, roomrot_z);
        roomE->calcBoundings();
        this->addRoomEntity(roomE);
        collisions.addRoom(roomE);
        ptree room_ents = (ptree) room.second.get_child("entities");

        BOOST_FOREACH(const ptree::value_type &entobj, room_ents) {
            string type = entobj.second.get<string>("type"), name = entobj.second.get<string>("name");
            e_loc x = entobj.second.get<float>("location.x"), y = entobj.second.get<float>("location.y"),
                    z = entobj.second.get<float>("location.z"), rx = entobj.second.get<float>("facing.x"),
                    ry = entobj.second.get<float>("facing.y"), rz = entobj.second.get<float>("facing.z");
            Entity *current_e = 0;
            boost::algorithm::to_lower(type);
            cout << "type " << type << endl;
            if (type == "object") {
                string objectbraces = "[OBJECT]";
                name = name.replace(name.find(objectbraces), objectbraces.length(), "");
                e_loc sc = entobj.second.get<e_loc>("scale");
                bool physics = entobj.second.get<bool>("physics");
                //shapef->setScale(sc);
                Shape *mshape = (Shape *) resman->get(entobj.second.get<string>("model"));
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
                collisions.addEntity((Entity *) oe);
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
    observer.setCamera(&default_Camera);
    observer.locate(jx, jy, jz);
    observer.face(rx, ry, rz);
    collisions.addEntity((Entity *) & observer);
    //observer.boundings[0]->rotate(-90,0,0);
    //texf->setWD(COMMON_DIR);
    Ballistic::Types::Texture *stex = (Ballistic::Types::Texture *) resman->get("@car.bmp");
    this->testsprite = new Sprite(stex);
    this->active_room = this->rooms[0];
    // octree=generateOctree(this->rooms);
    cout << "Loaded world" << endl;
    return true;
}

bool World::saveXml(string fn) {
    //TODO: No such node (vertices)
    ResourceManager *resman = ResourceManager::getInstance();
    cout << "Dumping to " << fn << endl;
    ptree root, level, rooms, room, r_location, r_shape, s_geom, s_counts, v_count, f_count,
            vpf, uv_count, s_faces, s_vertices, f_material, f_texture, r_entities;

    Shape *shape = this->active_room->getModel();

    v_count.put("", shape->v_count);
    f_count.put("", shape->f_count);
    uv_count.put("", shape->uv_count);
    vpf.put("", shape->v_per_poly);


    s_counts.add_child("vertices", v_count);
    s_counts.add_child("faces", f_count);
    s_counts.add_child("uvs", uv_count);
    s_counts.add_child("v_p_f", vpf);

    r_shape.put("name", "room");
    s_geom.add_child("counts", s_counts);


    //Faces
    for (size_t fi = 0; fi < shape->f_count; fi++) {
        ptree *p_face = new ptree(), *f_vertices = new ptree();
        if (shape->textures[fi]) {
            string tfn = resman->getResource(shape->textures[fi])->getOrigFilename();
            p_face->put("texture", tfn);
        }

        if (shape->materials[fi]) {
            ptree material, shining, emit;

            material.add_child("specular", makeRGBANode(shape->materials[fi]->getSpecular()));
            material.add_child("diffuse", makeRGBANode(shape->materials[fi]->getDiffuse()));
            material.put("shining", shape->materials[fi]->getShininess());
            material.put("emit", shape->materials[fi]->getEmission());

            p_face->add_child("material", material);
        }

        for (size_t vi = 0; vi < shape->v_per_poly; vi++) {
            ptree *p_vertex = new ptree(), *p_uv = new ptree();
            p_vertex->put("i", shape->faces[fi].index[vi]);
            *p_uv = makeUVNode(shape->faces[fi].uvs[vi].u, shape->faces[fi].uvs[vi].v);
            p_vertex->add_child("uv", *p_uv);
            f_vertices->add_child("vertex", *p_vertex);

            delete p_vertex;
            delete p_uv;
        }
        p_face->add_child("vertices", *f_vertices);
        s_faces.add_child("face", *p_face);
        delete p_face;
        delete f_vertices;
    }

    //Vertices
    for (size_t vi = 0; vi < shape->v_count; vi++) {
        ptree *vertex = new ptree(), *coords = new ptree(), *normal = new ptree();

        *coords = makeLocationNode(shape->vertices[vi].x, shape->vertices[vi].y, shape->vertices[vi].z);
        *normal = makeLocationNode(shape->normals[vi].x, shape->normals[vi].y, shape->normals[vi].z);
        vertex->add_child("coords", *coords);
        vertex->add_child("normal", *normal);
        s_vertices.add_child("vertex", *vertex);
        delete vertex;
        delete coords;
        delete normal;
    }

    s_geom.add_child("faces", s_faces);
    s_geom.add_child("vertices", s_vertices);
    r_shape.add_child("geom", s_geom);

    Coords rcoords = this->active_room->getCoords();
    ColorRGBA rambient = this->active_room->ambient_light;
    room.add_child("location", makeLocationNode(rcoords.translation.x, rcoords.translation.y, rcoords.translation.z));
    room.add_child("ambient_light", makeRGBANode(rambient.r, rambient.g, rambient.b, rambient.a));
    room.add_child("shape", r_shape);

    for (size_t i = 0; i<this->active_room->models.size(); i++) {
        ptree *r_entity = new ptree();

        r_entity->put("name", "[OBJECT]" + active_room->models[i]->name);
        r_entity->put("type", "object");
        r_entity->put("physics", (int) !active_room->models[i]->no_physics);
        r_entity->put("scale", 1.0f);

        Coords c = active_room->models[i]->getCoords();

        r_entity->add_child("location", makeTranslationNode(c));
        r_entity->add_child("facing", makeRotationNode(c));

        string model_file = resman->getResource(active_room->models[i]->model)->getOrigFilename();
        r_entity->put("model", model_file);
        r_entities.add_child("entity", *r_entity);

        delete r_entity;
    }

    for (size_t i = 0; i<this->active_room->lights.size(); i++) {
        ptree *r_entity = new ptree();
        r_entity->put("name", active_room->lights[i]->name);
        r_entity->put("type", "light");
        Coords c = active_room->lights[i]->getCoords();
        /*
         TODO: pass and load diffuse and specular here,
         *      load and pass energy here
         */
        ColorRGBA dc = active_room->lights[i]->getDiffuse();
        r_entity->put("r", dc.r);
        r_entity->put("g", dc.g);
        r_entity->put("b", dc.b);
        r_entity->put("energy", 1.0f);
        r_entity->add_child("location", makeTranslationNode(c));
        r_entity->add_child("facing", makeRotationNode(c));
        r_entities.add_child("entity", *r_entity);
        delete r_entity;
    }

    room.add_child("entities", r_entities);
    rooms.add_child("room", room);


    level.add_child("rooms", rooms);
    root.add_child("level", level);

    this->active_room;

    write_xml(fn, root);

}