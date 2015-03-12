#include "io/sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
    e_loc f = PI / 180.0;
    return deg*f;
}

size_t SdlControls::anykey(const Uint8 *state, int ksize) {
    size_t ret = 0;
    for (size_t i = 0; i < ksize; i++) {
        if (state[i]) {
            ret++;
        }
    }
    return ret;
}

void SdlControls::operator()() {

   
    while (!EngineState::getInstance()->exit()) {
          PyScripting::getInstance()->broadcast("TestSig");
          
    }
}