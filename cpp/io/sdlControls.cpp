#include "io/sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
    e_loc f = PI / 180.0;
    return deg*f;
}

size_t sdlControls::anykey(const Uint8 *state, int ksize) {
    size_t ret = 0;
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
    static e_loc rotx = 0, roty = 0, oldroty = 0;
    static e_loc z = 0;
    e_loc xx;
    int x, y, winw = config::getInstance()->getVD()->width / 2, winh = config::getInstance()->getVD()->height / 2;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    TrRot vel;
    int ksize = 255;
    size_t keys_p = 0;
    static Uint32 mouse_state, old_mouse_state;
    static bool oldl = false, oldr, oldm;
    while (!engineState::getInstance()->exit()) {
        const Uint8 *state = SDL_GetKeyboardState(&ksize);
        mouse_state = SDL_GetRelativeMouseState(&x, &y);

        xx = 0;

        xx = x;
        rotx += x;
        roty += y;

        rotx = normalizeRotation(rotx);

        vel = o->getVelocity();
        camera *c = o->getCamera();

        vel.reset();

        ObserverState *pstate = o->getState(), ostate = *pstate, bstate = *pstate;

        ostate.movement.reset();
        ostate.mouse.reset();


        if (state[SDL_SCANCODE_W]) {
            vel.t.y = -vstep;
            ostate.movement.up = true;
        }

        if (state[SDL_SCANCODE_S]) {
            vel.t.y = vstep;
            ostate.movement.down = true;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            ostate.movement.right = true;
        }

        if (state[SDL_SCANCODE_LEFT]) {
            ostate.movement.left = true;
        }

        if (state[SDL_SCANCODE_UP]) {
            ostate.movement.forward = true;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            ostate.movement.back = true;
            // o->bobHead();
        }


        ostate.mouse.left = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
        ostate.mouse.right = mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT);
        ostate.mouse.middle = mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE);

        if(abs(roty)+abs(y)+1>90) {
            //cout << "Here you go " << rotx << "\n";
            //  o->face((e_loc) roty, (e_loc) rotx, 0);
            o->rotate((e_loc)0,(e_loc)x,0);
            roty-=y;
        } else {
             o->rotate((e_loc)y,(e_loc)x,0);
        }
        //o->face((e_loc) roty, (e_loc) rotx, 0);
        //o->rotate((e_loc)y,(e_loc)x,0);
        o->setState(&ostate);
        if (keys_p != anykey(state, ksize) || rotx != oldroty || mouse_state != old_mouse_state) {
            keys_p = anykey(state, ksize);
            oldroty = rotx;
            
          
            old_mouse_state=mouse_state;

            
            
            o->refreshState();

        }
    }
}