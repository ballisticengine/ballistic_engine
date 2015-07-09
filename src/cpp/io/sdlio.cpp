#include "io/sdlio.hpp"
SDL_Window *SdlIO::window = 0;
SDL_Renderer *SdlIO::displayRenderer = 0;
SDL_Surface *SdlIO::screen = 0;
SdlIO *SdlIO::me = 0;
int SdlIO::window_w = 0;
int SdlIO::window_h = 0;

SdlIO::SdlIO() {
    w = World::getInstance();

    EngineState::getInstance()->setBool("keypress", false);
}

void SdlIO::setRenderer(RendererAbstract *r) {
    this->r = r;
}

RendererAbstract *SdlIO::getRenderer() {
    return this->r;
}

void SdlIO::initWindow(SdlIO *me) {
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_Init(SDL_INIT_VIDEO);
    TTF::getInstance();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(Config::getInstance()->getVD()->width, Config::getInstance()->getVD()->height,
            SDL_WINDOW_OPENGL, &SdlIO::window, &SdlIO::displayRenderer);
    SdlIO::screen = SDL_GetWindowSurface(SdlIO::window);
    SDL_GLContext context;
    SdlIO::me = me;
    context = SDL_GL_CreateContext(window);
    SdlIO::me->window_w = Config::getInstance()->getVD()->width;
    SdlIO::me->window_h = Config::getInstance()->getVD()->height;
    if (EngineState::getInstance()->getBool("fullscreen")) {
        toggleFullscreen();
    }

}

void SdlIO::flush() {
    SDL_GL_SwapWindow(SdlIO::window);
}

void SdlIO::toggleFullscreen() {
    bool fullscreen = EngineState::getInstance()->getBool("fullscreen");
    if (!fullscreen) {

        if (EngineState::getInstance()->getBool("desktop_fs")) {

            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN);
            int w, h;
            SDL_GetWindowSize(SdlIO::window, &w, &h);
            Config::getInstance()->getVD()->width = w;
            Config::getInstance()->getVD()->height = h;

        } else {

            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

        }

    } else {
        if (EngineState::getInstance()->getBool("desktop_fs")) {
            Config::getInstance()->getVD()->width = SdlIO::me->window_w;
            Config::getInstance()->getVD()->height = SdlIO::me->window_h;
        }
        SDL_SetWindowFullscreen(window, 0);
    }

    SdlIO::me->r->setVideoMode();
    EngineState::getInstance()->toggleBool("fullscreen");
}

size_t SdlIO::anykey(const Uint8 *state, int ksize) {
    size_t ret = 0;
    for (size_t i = 0; i < ksize; i++) {
        if (state[i]) {
            ret++;
        }
    }
    return ret;
}

void SdlIO::keyboardInputThread() {
    static const Uint8 * keyboard_state;
    int ksize = 255;
    static int last_num_keys = 0, down_count = 0, up_count = 0;
    Uint8 last_keys[ksize], before_keys[ksize];
    memset(last_keys, 0, ksize);
    memset(before_keys, 0, ksize);
    while (!EngineState::getInstance()->getBool("exit")) {
        keyboard_state = SDL_GetKeyboardState(&ksize);
        down_count = 0;
        up_count = 0;

        for (size_t i = 0; i < ksize; i++) {
            //
            if (keyboard_state[i] == 1) {
                down_count++;

            } else {
                if (last_keys[i] == 1) {
                    up_count++;
                }
            }
            last_keys[i] = keyboard_state[i];
        }

        if (down_count) {
            PyScripting::getInstance()->broadcast("KeyDown", &keyboard_state);
        }

        if (up_count) {
            PyScripting::getInstance()->broadcast("KeyUp", (void *)keyboard_state);
        }
    }
}

void SdlIO::mouseInputThread() {
    static int mouse_x, mouse_y, last_x, last_y, delta_x, delta_y;
    SDL_GetMouseState(&last_x, &last_y);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    static Uint32 mouse_state;
    while (!EngineState::getInstance()->getBool("exit")) {
        delta_x = delta_y = 0;
        mouse_state = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
        if (mouse_x) {

            delta_x = mouse_x + last_x;
            last_x = mouse_x;

        }

        if (mouse_y) {

            delta_y = mouse_y + last_y;
            last_y = mouse_y;
        }

        if (delta_x != 0 || delta_y != 0) {
            PyScripting::getInstance()->broadcast("MouseMove", &mouse_x, &mouse_y);
        }
        //mouse_x = mouse_y = delta_x = delta_y = 0;
    }
}

void SdlIO::inputThread() {
    Uint32 mouse_state;

    int mouse_x, mouse_y, last_x, last_y, delta_x, delta_y;
    SDL_GetMouseState(&last_x, &last_y);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    int ksize = 255, last_num_keys = 0, num_keys;
    Uint8 last_keys[ksize];
    memset(last_keys, 0, ksize);

    while (!EngineState::getInstance()->getBool("exit")) {
        delta_x = delta_y = 0;
        mouse_state = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

        if (mouse_x) {

            delta_x = mouse_x + last_x;
            last_x = mouse_x;

        }

        if (mouse_y) {

            delta_y = mouse_y + last_y;
            last_y = mouse_y;
        }

        if (delta_x != 0 || delta_y != 0) {
            PyScripting::getInstance()->broadcast("MouseMove", &mouse_x, &mouse_y);
        }

        const Uint8 *keyboard_state = SDL_GetKeyboardState(&ksize);
        int down_count = 0, up_count = 0;

        for (size_t i = 0; i < ksize; i++) {
            if (keyboard_state[i] == 1) {
                down_count++;

            } else {
                if (last_keys[i] == 1) {
                    up_count++;
                }
            }
            last_keys[i] = keyboard_state[i];
        }

        if (down_count) {
            PyScripting::getInstance()->broadcast("KeyDown", &keyboard_state);
        }

        if (up_count) {
           // cout << "KEYUP" << endl;
            // Its invoked on mousemove
             PyScripting::getInstance()->broadcast("KeyUp", last_keys); //GPF
        }

        mouse_x = mouse_y = delta_x = delta_y = 0;
    }

}

void SdlIO::eventLoop() {

    SDL_Event event;
    float rot = 0, tr = 0;



    Coords vel;
    while (!EngineState::getInstance()->getBool("exit")) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                EngineState::getInstance()->setBool("exit", true);
            }

            if (event.type == SDL_KEYDOWN) { //Maybe move io thread logic here...
                EngineState::getInstance()->setBool("keypress", true);

                PyScripting::getInstance()->broadcast("KeyPress", (void *)&event.key.keysym.sym);
                switch (event.key.keysym.sym) {
                    
                    
                    case SDLK_F1:
                        //wireframes
                        EngineState::getInstance()->toggleBool("debug_visual");
                        break;

                    case SDLK_F2:
                        //ligthing
                        EngineState::getInstance()->toggleBool("lighting");
                        break;

                    case SDLK_F3:
                        EngineState::getInstance()->toggleBool("noclip");
                        break;

                    case SDLK_f:
                        toggleFullscreen();

                        break;

                    case SDLK_w:

                        break;

                    case SDLK_s:

                        break;

                    case SDLK_ESCAPE:
                        EngineState::getInstance()->setBool("exit", true);
                        break;
                }

            }

            if (event.type == SDL_KEYUP) {
                EngineState::getInstance()->setBool("keypress", false);

                switch (event.key.keysym.sym) {
                    case SDLK_LEFTBRACKET:


                        break;

                    case SDLK_RIGHTBRACKET:


                        break;
                }

            } else {

            }

        }
        r->render();
    }
}

SdlIO::~SdlIO() {
    SDL_Quit();
}

extern "C" {

    void * returnSdlIo() {
        return (void *) SdlIO::getInstance();
    }
}