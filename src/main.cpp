#include <cstdlib>


#include "engine/engine.hpp"

using namespace std;


int main(int argc, char** argv) {
    
    Engine *e=(Engine *)Engine::getInstance();
   
    e->prepare();
    e->start();
   
    return 0;
}

