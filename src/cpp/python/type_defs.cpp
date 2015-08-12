#include "python/type_defs.hpp"

BOOST_PYTHON_MODULE(EngineTypes) {
    bp::class_<Vector3d, Vector3d *>("Vector3d")
            .def_readwrite("x", &Vector3d::x)
            .def_readwrite("y", &Vector3d::y)
            .def_readwrite("z", &Vector3d::z)
            .def("write", &Vector3d::write)
            ;
    bp::class_<Coords, Coords *>("Coords")
            .def_readwrite("rotation", &Coords::rotation)
            .def_readwrite("translation", &Coords::translation)
            .def_readwrite("r", &Coords::rotation)
            .def_readwrite("t", &Coords::translation)
            .def("reset", &Coords::reset)
            ;
}

void init_types() {
    initEngineTypes();
}