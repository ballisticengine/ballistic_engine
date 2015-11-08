#include "io/sdlio.hpp"
#include "world/WorldManager.hpp"

int SdlIO::window_w = 0;
int SdlIO::window_h = 0;

SdlIO::SdlIO() {
    w = WorldManager::getInstance()->getCurrentWorld();;
    rendering = RenderingManager::getInstance();
    EngineState::getInstance()->setBool("keypress", false);
    key_bindings = Config::getInstance()->getKeyBindings();
}


void SdlIO::initWindow() {
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
    SDLIOInterface::screen = SDL_GetWindowSurface(SdlIO::window);
    SDL_GLContext context;
   
    context = SDL_GL_CreateContext(window);
    this->window_w = Config::getInstance()->getVD()->width;
    this->window_h = Config::getInstance()->getVD()->height;
    if (EngineState::getInstance()->getBool("fullscreen")) {
        toggleFullscreen();
    }

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
//            Config::getInstance()->getVD()->width = SdlIO::me->window_w;
//            Config::getInstance()->getVD()->height = SdlIO::me->window_h;
        }
        SDL_SetWindowFullscreen(window, 0);
    }

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
    key_action_map kmap = key_bindings->getBindings();
    UI *ui = UI::getInstance();
    while (!EngineState::getInstance()->getBool("exit")) {
       // ui->kb_m.lock();
        if(!ui->m.try_lock()) {
            continue;
        }
        keyboard_state = SDL_GetKeyboardState(&ksize);
         ui->m.unlock();
        down_count = 0;
        up_count = 0;

        for (size_t i = 0; i < ksize; i++) {
            if (keyboard_state[i] == 1) {
                // cout << i << endl;
                down_count++;
                KeybindAction action = kmap[i];
                PyScripting::getInstance()->enqueue(action.name,{0}, true); //TO WYDUPIA

            } else {
                if (last_keys[i] == 1) {
                    up_count++;
                }
            }
            last_keys[i] = keyboard_state[i];
        }

       PyScripting::getInstance()->runQueue();

        if (down_count) {
            PyScripting::getInstance()->broadcast("key_down",{&keyboard_state});
        }

        if (up_count) {
            // cout << "Up count " << up_count << endl;
            PyScripting::getInstance()->broadcast("key_up",{(void *) keyboard_state});
        }
       
    }
}

void SdlIO::attachMouse(bool attach) {
    if (attach) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void SdlIO::mouseInputThread() {
    static int mouse_x, mouse_y, last_x, last_y, delta_x, delta_y;
    SDL_GetMouseState(&last_x, &last_y);
    
    static Uint32 mouse_state;
    while (!EngineState::getInstance()->getBool("exit")) {
      
        if (EngineState::getInstance()->getBool("attach_mouse")) {
            attachMouse();
        } else {
            attachMouse(false);
        }
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
            PyScripting::getInstance()->broadcast("mouse_move",{&mouse_x, &mouse_y});
        }

        if (mouse_state) {
            PyScripting::getInstance()->broadcast("mouse_click",{&mouse_state});
        }

        //mouse_x = mouse_y = delta_x = delta_y = 0;
    }
}

void SdlIO::eventLoop() {
    SDL_Event event;
    UI *ui = UI::getInstance();
    key_action_map kmap = key_bindings->getBindings();
    while (!EngineState::getInstance()->getBool("exit")) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                EngineState::getInstance()->setBool("exit", true);
            }

            if (event.type == SDL_KEYDOWN) {
                EngineState::getInstance()->setBool("keypress", true);
                PyScripting::getInstance()->broadcast("key_press",{(void *) &event.key.keysym.sym});
            }

            PyScripting::getInstance()->lockWait();
            ui->processSDLEvent(event);
            PyScripting::getInstance()->m.unlock();
        }
        
        rendering->render();
        

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