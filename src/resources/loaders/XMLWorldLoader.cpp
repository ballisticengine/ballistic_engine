#include "resources/loaders/XMLWorldLoader.hpp"
#include "world/World.hpp"
#include "types/skybox.hpp"
#include "resources/ResourceManager.hpp"
#include "libload/LibLoad.hpp"
#include "types/Vector3d.hpp"

using boost::property_tree::ptree;

extensions_s XMLWorldLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("xml");
    return exts;
}

XMLWorldLoader::XMLWorldLoader() {

}

void *XMLWorldLoader::load(string level_name) {
    ResourceManager *resman = ResourceManager::getInstance();
    World *w = new World();
    ptree pt;
    read_xml(level_name, pt,
            boost::property_tree::xml_parser::trim_whitespace
            | boost::property_tree::xml_parser::no_comments);

    string skyfn = pt.get<string>("level.config.skybox");
    Ballistic::Types::Texture *sky_texture;
    this->addDependency(skyfn, (void **) &sky_texture);
    resman->resolveAllDependencies();
    w->sky = new Skybox(sky_texture);
    w->sky->makeShape(20, 20);
            
    ptree& jump_point = pt.get_child("level.config.jump_point");

    scalar_t jx = jump_point.get<scalar_t>("x"),
            jy = jump_point.get<scalar_t>("y"),
            jz = jump_point.get<scalar_t>("z"),
            rx = jump_point.get<scalar_t>("rx"),
            ry = jump_point.get<scalar_t>("ry"),
            rz = jump_point.get<scalar_t>("rz");


    ptree &rooms = pt.get_child("level.rooms");
    Loader *xml_loader = (Loader *) LibLoad::getInstance()->getLoaderByExtension("xml", SHAPE);

    BOOST_FOREACH(const ptree::value_type &room, rooms) {
        ptree room_p = (ptree) room.second;
        Shape *room_shape = (Shape *) resman->get(room.second.get<string>("model"), SHAPE);
        resman->resolveAllDependencies();
        
        RoomEntity *roomE = new RoomEntity();


        roomE->ambient_light.r = room.second.get<scalar_t>("ambient_light.r"),
                roomE->ambient_light.b = room.second.get<scalar_t>("ambient_light.b"),
                roomE->ambient_light.g = room.second.get<scalar_t>("ambient_light.g");

        roomE->name = room.second.get<string>("name");
        roomE->setModel(room_shape);
        scalar_t
        rx = room.second.get<scalar_t>("location.x"),
                ry = room.second.get<scalar_t>("location.y"),
                rz = room.second.get<scalar_t>("location.z")
                ;
        roomE->locate(rx, ry, rz);
        roomE->calcBoundings();
        w->addRoomEntity(roomE);
        w->getPhysics()->addRoom(roomE); //TODO
        ptree room_ents = (ptree) room.second.get_child("entities");

        BOOST_FOREACH(const ptree::value_type &entobj, room_ents) {
            string type = entobj.second.get<string>("type"), name = entobj.second.get<string>("name");
            scalar_t x = entobj.second.get<float>("location.x"), y = entobj.second.get<float>("location.y"),
                    z = entobj.second.get<float>("location.z"), rx = entobj.second.get<float>("facing.x"),
                    ry = entobj.second.get<float>("facing.y"), rz = entobj.second.get<float>("facing.z");
            Entity *current_e = 0;
            boost::algorithm::to_lower(type);

            if (type == "object") {
                string objectbraces = "[OBJECT]";
                name = name.replace(name.find(objectbraces), objectbraces.length(), "");
                scalar_t sc = entobj.second.get<scalar_t>("scale");
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

                
                if(this->getBool("triangles")) {
                    cout << "USING TRIANGLES" << endl;
                    w->getPhysics()->addEntity(oe, true);
                } else {
                    w->getPhysics()->addEntity(oe);
                }
                
                


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
    w->getPhysics()->addEntity((ObjectEntity *) & w->observer);

    w->active_room = w->rooms[0];

    cout << "Loaded world" << endl;

    return (void *) w;
}

/*TODO adapt this to a new format */
bool XMLWorldLoader::save(World *world, string level_filename, string geometry_filename) {
    ResourceManager *resman = ResourceManager::getInstance();
    cout << "Dumping to " << level_filename << endl;
    ptree root, level, config, jumppoint, rooms, room, r_location, r_shape, s_geom, s_counts, v_count, f_count,
            vpf, uv_count, s_faces, s_vertices, f_material, f_texture, r_entities;


    /*
     * Config resman->getResource(shape->textures[fi])->getOrigFilename()
     */

    config.put("skybox", resman->getResource(world->sky->getTexture())->getOrigFilename());
    Coords jump_point_c;
    jump_point_c.rotation.x = 0;
    jump_point_c.rotation.y = 0;
    jump_point_c.rotation.z = 0;
    jump_point_c.translation.x = 0;
    jump_point_c.translation.y = 0;
    jump_point_c.translation.z = 0;

    config.add_child("jump_point", makeCoordsNode(jump_point_c));


    /*
     * Geometry
     */
    Shape *shape = world->active_room->getModel();

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

    Coords rcoords = world->active_room->getCoords();
    ColorRGBA rambient = world->active_room->ambient_light;
    room.add_child("location", makeLocationNode(rcoords.translation.x, rcoords.translation.y, rcoords.translation.z));
    room.add_child("ambient_light", makeRGBANode(rambient.r, rambient.g, rambient.b, rambient.a));
    room.add_child("shape", r_shape);

    for (size_t i = 0; i < world->active_room->models.size(); i++) {
        ptree *r_entity = new ptree();

        r_entity->put("name", "[OBJECT]" + world->active_room->models[i]->name);
        r_entity->put("type", "object");
        r_entity->put("physics", (int) !world->active_room->models[i]->no_physics);
        r_entity->put("scale", 1.0f);

        Coords c = world->active_room->models[i]->getCoords();

        r_entity->add_child("location", makeTranslationNode(c));
        r_entity->add_child("facing", makeRotationNode(c));

        string model_file = resman->getResource(world->active_room->models[i]->model)->getOrigFilename();
        r_entity->put("model", model_file);
        r_entities.add_child("entity", *r_entity);

        delete r_entity;
    }

    for (size_t i = 0; i < world->active_room->lights.size(); i++) {
        ptree *r_entity = new ptree();
        r_entity->put("name", world->active_room->lights[i]->name);
        r_entity->put("type", "light");
        Coords c = world->active_room->lights[i]->getCoords();
        /*
         TODO: pass and load diffuse and specular here,
         *      load and pass energy here
         */
        ColorRGBA dc = world->active_room->lights[i]->getDiffuse();
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
    level.add_child("config", config);
    root.add_child("level", level);

    write_xml(level_filename, root);
}

extern "C" {

    WorldLoader * returnLoader() {
        return (WorldLoader *) new XMLWorldLoader();
    }
}