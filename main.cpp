#include <cstdlib>


#include "engine.hpp"

using namespace std;


int main(int argc, char** argv) {
    Engine *e=(Engine *)Engine::getInstance();
    if(argc>1) {
        cout << "Model view mode\n";
        e->preview(string(argv[1]));
    } else {
    
    e->prepare();
    e->start();
    }
    return 0;
}

