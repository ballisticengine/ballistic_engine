#include "python/world_defs.hpp"

#include "python/null_deleter.hpp"


shared_ptr<world> getSharedWorldInstance()
{
	return shared_ptr<world>( world::getInstance(),NullDeleter() );
}

typedef boost::shared_ptr<world> world_ptr;
BOOST_PYTHON_MODULE(world)
{

	bp::class_<MathTypes::vector,MathTypes::vector *>("Vector3d")
		.def_readwrite("x",&MathTypes::vector::x)
		.def_readwrite("y",&MathTypes::vector::y)
		.def_readwrite("z",&MathTypes::vector::z)
		.def("write",&MathTypes::vector::write)
		;

	bp::class_<TrRot,TrRot *>("TrRot")
		.def_readwrite("t",&TrRot::t)
		.def_readwrite("r",&TrRot::r)
		.def("reset",&TrRot::reset)
		;

        bp::class_<coords,coords *>("coords")
        .def_readwrite("rotation",&coords::rotation)
        .def_readwrite("translation",&coords::translation)
        ;
	bp::class_<ShapeAbstract,ShapeAbstract *>("ShapeAbstract");
	bp::class_<shape,shape *,bp::bases<ShapeAbstract> >("shape");




	bp::class_<entity,entity *>("entity")
		.def("getCoords",&entity::getCoords)
		.def("locate",&entity::locate)
                .def("translate3",&entity::translate3)
		.def_readonly("name",&entity::name)
		.def_readonly("type",&entity::type)
		;



	bp::class_<PhysicalEntity,PhysicalEntity*,bp::bases<entity> >("PhysicalEntity")
		.def("getVelocity",&PhysicalEntity::getVelocity)
		.def("setVelocity",&PhysicalEntity::setVelocity)
		.def_readwrite("velocity",&PhysicalEntity::velocity)
                .def_readwrite("acceleration",&PhysicalEntity::acceleration)
                .def_readwrite("no_physics",&PhysicalEntity::no_physics)

		;


	bp::class_<ObjectEntity,ObjectEntity*,bp::bases<PhysicalEntity> >("ObjectEntity")
		.def_readwrite("model",&ObjectEntity::model)
		;

        
        
        bp::class_<ObserverMovement,ObserverMovement *>("ObserverMovement")
        .def_readwrite("forward",&ObserverMovement::forward)
        .def_readwrite("left",&ObserverMovement::left)
        .def_readwrite("right",&ObserverMovement::right)
        .def_readwrite("back",&ObserverMovement::back)
        .def_readwrite("up",&ObserverMovement::up)
        .def_readwrite("down",&ObserverMovement::down)
        ;
        
        bp::class_<ObserverMouse,ObserverMouse *>("ObserverMouse")
         .def_readwrite("left",&ObserverMouse::left)
         .def_readwrite("right",&ObserverMouse::right)
         .def_readwrite("middle",&ObserverMouse::middle)
        
        ;
        
        
        bp::class_<ObserverState,ObserverState *>("ObserverState")
        .def_readwrite("movement",&ObserverState::movement)
        .def_readwrite("mouse",&ObserverState::mouse)
        ;
        
        bp::class_<ObserverEntity,ObserverEntity*,bp::bases<PhysicalEntity> >("ObserverEntity")
            .def("bobHead",&ObserverEntity::bobHead)
            //.def("getCoords",&ObserverEntity::getCoords)
        
         //   .def("getState",&ObserverEntity::getState)
        //    .def("setState",&ObserverEntity::setState)
        ;
        
	bp::class_<obj_list>("obj_list")
		.def(bp::vector_indexing_suite<obj_list>() );


	bp::class_<roomEntity,roomEntity *,bp::bases<ObjectEntity> >("roomEntity")
		.def_readwrite("models",&roomEntity::models)
		;

	bp::class_<lights_list>("lights_list")
		.def(bp::vector_indexing_suite<lights_list>() );



	bp::class_<world,shared_ptr<world>,boost::noncopyable>("world",bp::no_init)//.add_property("instance", shared_ptr<&world::getInstance>())
		.def("getInstance",&getSharedWorldInstance )
		.def_readonly("active_room", &world::active_room)
		.def_readwrite("observer",&world::observer)
		.staticmethod("getInstance")
				
		;


};


void init_world() {
    initworld();
}


//////////////////



