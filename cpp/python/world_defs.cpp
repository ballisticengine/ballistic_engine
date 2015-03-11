#include "python/world_defs.hpp"

#include "python/null_deleter.hpp"

shared_ptr<World> getSharedWorldInstance() {
    return shared_ptr<World>(World::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<World> World_ptr;

BOOST_PYTHON_MODULE(World) {

    bp::class_<MathTypes::Vector3d, MathTypes::Vector3d *>("Vector3d")
            .def_readwrite("x", &MathTypes::Vector3d::x)
            .def_readwrite("y", &MathTypes::Vector3d::y)
            .def_readwrite("z", &MathTypes::Vector3d::z)
            .def("write", &MathTypes::Vector3d::write)
            ;

    bp::class_<TrRot, TrRot *>("TrRot")
            .def_readwrite("t", &TrRot::t)
            .def_readwrite("r", &TrRot::r)
            .def("reset", &TrRot::reset)
            ;

    bp::class_<Coords, Coords *>("Coords")
            .def_readwrite("rotation", &Coords::rotation)
            .def_readwrite("translation", &Coords::translation)
            ;
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


    bp::class_<CollsionInfo, CollsionInfo *>("CollsionInfo")
            .def_readonly("cvec", &CollsionInfo::cvec)
            .def_readonly("nameA", &CollsionInfo::nameA)
            .def_readonly("nameB", &CollsionInfo::nameB)
            ;

    bp::class_<Entity, Entity *>("Entity")
            .def("getCoords", &Entity::getCoords)
            .def("locate", &Entity::locate)
            .def("face", &Entity::face)
            .def("translate3", &Entity::translate3)
            .def_readonly("name", &Entity::name)
            .def_readonly("type", &Entity::type)
            .def_readwrite("subtype", &Entity::subtype)
            .def_readwrite("no_collisions", &Entity::no_collisions)
            ;



    bp::class_<PhysicalEntity, PhysicalEntity*, bp::bases<Entity> >("PhysicalEntity")
            .def("getVelocity", &PhysicalEntity::getVelocity)
            .def("setVelocity", &PhysicalEntity::setVelocity)
            .def_readwrite("velocity", &PhysicalEntity::velocity)
            .def_readwrite("acceleration", &PhysicalEntity::acceleration)
            .def_readwrite("no_physics", &PhysicalEntity::no_physics)
            .def_readwrite("weight", &PhysicalEntity::weight)
            ;


    bp::class_<ObjectEntity, ObjectEntity*, bp::bases<PhysicalEntity> >("ObjectEntity")
            .def_readwrite("model", &ObjectEntity::model)
            ;



    bp::class_<ObserverMovement, ObserverMovement *>("ObserverMovement")
            .def_readwrite("forward", &ObserverMovement::forward)
            .def_readwrite("left", &ObserverMovement::left)
            .def_readwrite("right", &ObserverMovement::right)
            .def_readwrite("back", &ObserverMovement::back)
            .def_readwrite("up", &ObserverMovement::up)
            .def_readwrite("down", &ObserverMovement::down)
            .def_readwrite("prev_weapon", &ObserverMovement::prev_weapon)
            .def_readwrite("next_weapon", &ObserverMovement::next_weapon)
            ;

    bp::class_<ObserverMouse, ObserverMouse *>("ObserverMouse")
            .def_readwrite("left", &ObserverMouse::left)
            .def_readwrite("right", &ObserverMouse::right)
            .def_readwrite("middle", &ObserverMouse::middle)
            .def_readwrite("leftclick", &ObserverMouse::leftclick)
            .def_readwrite("rightclick", &ObserverMouse::rightclick)
            .def_readwrite("middleclick", &ObserverMouse::middleclick)

            ;


    bp::class_<ObserverState, ObserverState *>("ObserverState")
            .def_readwrite("movement", &ObserverState::movement)
            .def_readwrite("mouse", &ObserverState::mouse)
            ;

    bp::class_<ObserverEntity, ObserverEntity*, bp::bases<PhysicalEntity> >("ObserverEntity")
            .def("bobHead", &ObserverEntity::bobHead)
            .def("kickBack", &ObserverEntity::kickBack)
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
            .def("placeDecal", &RoomEntity::placeDecal)
            .def("placePreloadDecal", &RoomEntity::placePreloadDecal)
            .def("placeDecalTexture", &RoomEntity::placeDecalTexture)
            .def("spawnObject", &RoomEntity::spawnObject, bp::return_value_policy<bp::reference_existing_object>())
            .def("spawnShape", &RoomEntity::spawnShape, bp::return_value_policy<bp::reference_existing_object>())
            .def("removeObjectEntity", &RoomEntity::removeObjectEntity)
            ;

    bp::class_<lights_list>("lights_list")
            .def(bp::vector_indexing_suite<lights_list>());



    bp::class_<World, shared_ptr<World>, boost::noncopyable>("World", bp::no_init)//.add_property("instance", shared_ptr<&World::getInstance>())
            .def("getInstance", &getSharedWorldInstance)
            .def_readonly("active_room", &World::active_room)
            .def_readwrite("observer", &World::observer)

            .staticmethod("getInstance")

            ;


};

void init_world() {
    initWorld();
}


//////////////////



