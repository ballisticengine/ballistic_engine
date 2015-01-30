#include "python/world_defs.hpp"

#include "python/null_deleter.hpp"

shared_ptr<world> getSharedWorldInstance() {
    return shared_ptr<world>(world::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<world> world_ptr;

BOOST_PYTHON_MODULE(world) {

    bp::class_<MathTypes::vector, MathTypes::vector *>("Vector3d")
            .def_readwrite("x", &MathTypes::vector::x)
            .def_readwrite("y", &MathTypes::vector::y)
            .def_readwrite("z", &MathTypes::vector::z)
            .def("write", &MathTypes::vector::write)
            ;

    bp::class_<TrRot, TrRot *>("TrRot")
            .def_readwrite("t", &TrRot::t)
            .def_readwrite("r", &TrRot::r)
            .def("reset", &TrRot::reset)
            ;

    bp::class_<coords, coords *>("coords")
            .def_readwrite("rotation", &coords::rotation)
            .def_readwrite("translation", &coords::translation)
            ;
    bp::class_<ShapeAbstract, ShapeAbstract *>("ShapeAbstract");
    bp::class_<shape, shape *, bp::bases<ShapeAbstract> >("shape");


    bp::class_<BoundingCube, BoundingCube *>("BoundingCube")
        .def_readonly("name",&BoundingCube::name)
        .def_readonly("max",&BoundingCube::max)
        .def_readonly("min",&BoundingCube::max)
        .def_readonly("loc",&BoundingCube::loc)
        .def_readonly("width",&BoundingCube::width)
        .def_readonly("height",&BoundingCube::height)
        .def_readonly("depth",&BoundingCube::depth)
    ;

    
    bp::class_<collsionInfo, collsionInfo *>("collsionInfo")
        .def_readonly("cvec",&collsionInfo::cvec)
        .def_readonly("nameA",&collsionInfo::nameA)
        .def_readonly("nameB",&collsionInfo::nameB)
    ;
    
    bp::class_<entity, entity *>("entity")
            .def("getCoords", &entity::getCoords)
            .def("locate", &entity::locate)
            .def("face",&entity::face)
            .def("translate3", &entity::translate3)
            .def_readonly("name", &entity::name)
            .def_readonly("type", &entity::type)
            .def_readwrite("subtype",&entity::subtype)
            .def_readwrite("no_collisions",&entity::no_collisions)
            ;



    bp::class_<PhysicalEntity, PhysicalEntity*, bp::bases<entity> >("PhysicalEntity")
            .def("getVelocity", &PhysicalEntity::getVelocity)
            .def("setVelocity", &PhysicalEntity::setVelocity)
            .def_readwrite("velocity", &PhysicalEntity::velocity)
            .def_readwrite("acceleration", &PhysicalEntity::acceleration)
            .def_readwrite("no_physics", &PhysicalEntity::no_physics)
            .def_readwrite("weight",&PhysicalEntity::weight)
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
            .def_readwrite("current_weapon",&ObserverEntity::current_weapon)
    //.def("getCoords",&ObserverEntity::getCoords)

            //   .def("getState",&ObserverEntity::getState)
            //    .def("setState",&ObserverEntity::setState)
            ;
    
    bp::class_<Weapon, Weapon*, bp::bases<entity> >("Weapon")
        .def_readonly("initial_velocity",&Weapon::initial_velocity)
        .def_readonly("decal",&Weapon::decal)
        .def_readonly("bullet",&Weapon::bullet)
        .def_readonly("display_name",&Weapon::display_name)
        .def_readonly("next",&Weapon::next)
        .def_readonly("prev",&Weapon::prev)
        
    ;
    
    bp::class_<obj_list>("obj_list")
            .def(bp::vector_indexing_suite<obj_list>());

    
    bp::class_<Sprite,Sprite *,bp::bases<entity> >("Sprite");

    bp::class_<roomEntity, roomEntity *, bp::bases<ObjectEntity> >("roomEntity")
            .def_readwrite("models", &roomEntity::models)
            .def("placeDecal",&roomEntity::placeDecal)
            .def("placePreloadDecal",&roomEntity::placePreloadDecal)
            .def("placeDecalTexture",&roomEntity::placeDecalTexture)
            .def("spawnObject", &roomEntity::spawnObject,bp::return_value_policy<bp::reference_existing_object>())
            .def("spawnShape", &roomEntity::spawnShape,bp::return_value_policy<bp::reference_existing_object>()) 
            .def("removeObjectEntity",&roomEntity::removeObjectEntity)
    ;

    bp::class_<lights_list>("lights_list")
            .def(bp::vector_indexing_suite<lights_list>());



    bp::class_<world, shared_ptr<world>, boost::noncopyable>("world", bp::no_init)//.add_property("instance", shared_ptr<&world::getInstance>())
            .def("getInstance", &getSharedWorldInstance)
            .def_readonly("active_room", &world::active_room)
            .def_readwrite("observer", &world::observer)
            
            .staticmethod("getInstance")

            ;


};

void init_world() {
    initworld();
}


//////////////////



