#include "factory.hpp"
#include "sdlio.h"

factory::factory() {
    this->map["io"]=new sdlIO();
}