#include "io/sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
    e_loc f = PI / 180.0;
    return deg*f;
}

size_t sdlControls::anykey(const Uint8 *state, int ksize) {
    size_t ret=0;
    for (size_t i = 0; i < ksize; i++) {
        if (state[i]) {
            ret++;
        }
    }
    return ret;
}

void sdlControls::operator()() {

    ObserverEntity *o = world::getInstance()->getObserver();
    e_loc step = 0.09, rstep = 0.1, vstep = 50;
    static e_loc rotx = 0;
    static e_loc z = 0;
    e_loc xx;
    int x, y, winw = config::getInstance()->getVD()->width / 2, winh = config::getInstance()->getVD()->height / 2;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    TrRot vel;
    int ksize = 255;
    size_t keys_p=0;
    while (!engineState::getInstance()->exit()) {
        const Uint8 *state = SDL_GetKeyboardState(&ksize);
        SDL_GetRelativeMouseState(&x, &y);

        xx = 0;

        xx = x;
        rotx += x;

        rotx = normalizeRotation(rotx);

        vel = o->getVelocity();
        camera *c = o->getCamera();
        
        vel.reset();

        ObserverState *pstate=o->getState(), ostate = *pstate,bstate=*pstate;
        
        ostate.movement.reset();
        

        if (state[SDL_SCANCODE_W]) {
            vel.t.y = -vstep;
            ostate.movement.up = true;
        } 

        if (state[SDL_SCANCODE_S]) {
            vel.t.y = vstep;
            ostate.movement.down = true;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            vel.t.x += -cos(deg2rad(rotx)) * vstep;
            vel.t.z += -sin(deg2rad(rotx)) * vstep;
            ostate.movement.right = true;
            // o->bobHead();
        }

        if (state[SDL_SCANCODE_LEFT]) {
            vel.t.x += cos(deg2rad(rotx)) * vstep;
            vel.t.z += sin(deg2rad(rotx)) * vstep;
            ostate.movement.left = true;
            //o->bobHead();
        }

        if (state[SDL_SCANCODE_UP]) {
            ostate.movement.forward = true;
            vel.t.x += -sin(deg2rad(rotx)) * vstep;
            vel.t.z += cos(deg2rad(rotx)) * vstep;
            //o->bobHead();
        }

        if (state[SDL_SCANCODE_DOWN]) {
            ostate.movement.back = true;
            vel.t.x += sin(deg2rad(rotx)) * vstep;
            vel.t.z += -cos(deg2rad(rotx)) * vstep;
            // o->bobHead();
        }

        

        o->setState(&ostate);
        if(keys_p!=anykey(state,ksize)) {
            keys_p=anykey(state,ksize);
            o->refreshState();
        }
        
        o->setVelocity(vel);
        o->rotate(0, (e_loc) xx, 0);
        o->rotate((e_loc) y, 0, 0);


    }

}