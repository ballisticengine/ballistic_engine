#include <cstdlib>


#include "engine.hpp"

using namespace std;


int main(int argc, char** argv) {
    engine *e=(engine *)engine::getInstance();
    if(argc>1) {
        cout << "Model view mode\n";
        e->preview(string(argv[1]));
    } else {
    
    e->prepare();
    e->start();
    }
    return 0;
}

