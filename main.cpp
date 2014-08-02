#include <cstdlib>


#include "engine.hpp"

using namespace std;


int main(int argc, char** argv) {
    engine *e=(engine *)engine::getInstance();
    e->prepare();
    e->start();
    return 0;
}

