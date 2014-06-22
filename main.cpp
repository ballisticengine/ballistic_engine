

#include <cstdlib>


#include "sdlio.hpp"

using namespace std;


int main(int argc, char** argv) {
    sdlIO *io=new sdlIO();
    io->initWindow();
    io->eventLoop();
    return 0;
}

