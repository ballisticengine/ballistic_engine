#include "python/world_defs.hpp"

#include "python/null_deleter.hpp"

boost::shared_ptr<World> getSharedWorldInstance() {
    return boost::shared_ptr<World>(World::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<World> World_ptr;

BOOST_PYTHON_MODULE(World) {
    
  
    bp::class_<ShapeAbstract, ShapeAbstract *>("ShapeAbstract");
    bp::class_<Shape, Shape *, bp::bases<ShapeAbstract> >("Shape");


    bp::class_<BoundingCube, BoundingCube *>("BoundingCube")
            .def_readonly("name", &BoundingCube::name)
            .def_readonly("max", &BoundingCube::max)
            .def_readonly("min", &BoundingCube::max)
            .def_readonly("loc", &BoundingCube::loc)
            .def_readonly("width", &BoundingCube::width)
            .def_readonly("height", &BoundingCube::height)
            .def_readonly("depth", &BoundingCube::depth)
            ;

    bp::class_<CollisionParty, CollisionParty *>("CollisionInfo")
        .def_readonly("cvec",&CollisionParty::cvec)
        .def_readonly("name",&CollisionParty::name)
        .def_readonly("diff",&CollisionParty::diff)
    ;
    
    bp::class_<CollisionInfo, CollisionInfo *>("CollisionInfo")
            .def_readonly("A", &CollisionInfo::A)
            .def_readonly("B", &CollisionInfo::B)
            .def_readonly("distance", &CollisionInfo::distance)
            .def_readonly("collided", &CollisionInfo::collided)
            ;

    bp::class_<Entity, Entity *>("Entity")
            .def("get_coords", &Entity::getCoords)
            .def("locate", &Entity::locate)
            .def("face", &Entity::face)
            .def("translate3", &Entity::translate3)
            .def_readonly("name", &Entity::name)
            .def_readonly("type", &Entity::type)
            .def_readwrite("subtype", &Entity::subtype)
            .def_readwrite("no_collisions", &Entity::no_collisions)
            ;

    bp::class_<ObjectEntity, ObjectEntity*, bp::bases<Entity> >("ObjectEntity")
            .def("get_velocity", &ObjectEntity::getVelocity)
            .def("set_velocity", &ObjectEntity::setVelocity)
            .def_readwrite("velocity", &ObjectEntity::velocity)
            .def_readwrite("acceleration", &ObjectEntity::acceleration)
            .def_readwrite("no_physics", &ObjectEntity::no_physics)
            .def_readwrite("weight", &ObjectEntity::weight)
            .def_readwrite("model", &ObjectEntity::model)
            ;
 
    bp::class_<ObserverEntity, ObserverEntity*, bp::bases<ObjectEntity> >("ObserverEntity")
            .def("bob_head", &ObserverEntity::bobHead)
            .def("kick_back", &ObserverEntity::kickBack)
            .def("face", &ObserverEntity::face)
            .def("rotate", &ObserverEntity::rotate)
            .def_readwrite("current_weapon", &ObserverEntity::current_weapon)
            ;

    bp::class_<Weapon, Weapon*, bp::bases<Entity> >("Weapon")
            .def_readonly("initial_velocity", &Weapon::initial_velocity)
            .def_readonly("decal", &Weapon::decal)
            .def_readonly("bullet", &Weapon::bullet)
            .def_readonly("display_name", &Weapon::display_name)
            .def_readonly("next", &Weapon::next)
            .def_readonly("prev", &Weapon::prev)

            ;

    bp::class_<obj_list>("obj_list")
            .def(bp::vector_indexing_suite<obj_list>());


    bp::class_<Sprite, Sprite *, bp::bases<Entity> >("Sprite");

    bp::class_<RoomEntity, RoomEntity *, bp::bases<ObjectEntity> >("RoomEntity")
            .def_readwrite("models", &RoomEntity::models)
            .def("place_decal", &RoomEntity::placeDecal)
            .def("place_preload_decal", &RoomEntity::placePreloadDecal)
            .def("place_decal_texture", &RoomEntity::placeDecalTexture)
            .def("spawn_object", &RoomEntity::spawnObject, bp::return_value_policy<bp::reference_existing_object>())
            .def("spawn_shape", &RoomEntity::spawnShape, bp::return_value_policy<bp::reference_existing_object>())
            .def("remove_object_entity", &RoomEntity::removeObjectEntity)
            ;

    bp::class_<lights_list>("lights_list")
            .def(bp::vector_indexing_suite<lights_list>());

    bp::class_<BulletPhysics, BulletPhysics *>("Physics")
        .def("ray_test", &BulletPhysics::rayTest)
    ;
    
    bp::class_<World, boost::shared_ptr<World>, boost::noncopyable>("World", bp::no_init)
            .def("get_instance", &getSharedWorldInstance)
            .def_readonly("active_room", &World::active_room)
            .def_readwrite("observer", &World::observer)
            .staticmethod("get_instance")
            .def("save_xml", &World::saveXml)
            .def("get_physics", &World::getPhysicsEngine)
            ;
    
    

};

void init_world() {
    initWorld();
}


//////////////////



