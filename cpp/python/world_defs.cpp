#include "python/world_defs.hpp"


struct NullDeleter
{
	void operator()(const void*){}
};

shared_ptr<world> getSharedInstance()
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

		;


	bp::class_<ObjectEntity,ObjectEntity*,bp::bases<PhysicalEntity> >("ObjectEntity")
		.def_readwrite("model",&ObjectEntity::model)
		;

	bp::class_<obj_list>("obj_list")
		.def(bp::vector_indexing_suite<obj_list>() );


	bp::class_<roomEntity,roomEntity *,bp::bases<ObjectEntity> >("roomEntity")
		.def_readwrite("models",&roomEntity::models)
		;

	bp::class_<lights_list>("lights_list")
		.def(bp::vector_indexing_suite<lights_list>() );



	bp::class_<world,shared_ptr<world>,boost::noncopyable>("world",bp::no_init)//.add_property("instance", shared_ptr<&world::getInstance>())
		.def("getInstance",&getSharedInstance )
		.def_readonly("active_room", &world::active_room)
		
		.staticmethod("getInstance")
				
		;


};


void init_world() {
    initworld();
}


//////////////////



