#include "modelview.hpp"
SDL_Window *ModelView::window = 0;
SDL_Renderer *ModelView::displayRenderer = 0;
SDL_Surface *ModelView::screen = 0;
Renderer *ModelView::r = 0;

void ModelView::initWindow() {
     SDL_Init(SDL_INIT_VIDEO);
   
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(800, 600,
            SDL_WINDOW_OPENGL, &ModelView::window, &ModelView::displayRenderer);
    ModelView::screen = SDL_GetWindowSurface(ModelView::window);
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);
    ModelView::r=new Renderer();
    r->basicinit();
}

 void ModelView::eventLoop() {
      SDL_Event event; 
     while (!exit) {
        while (SDL_PollEvent(& event)) {
             if (event.type == SDL_QUIT) {
                 exit=true;
             }
             r->render();
        }
      }
 }
 
 ModelView::ModelView() {
    
 }

 ModelView::~ModelView() {
     delete r;
     SDL_Quit(); 
 }

int main(int argc,char **argv) {
    cout << "Ballistic model viewer\n";
    ModelView app;
    app.initWindow();
    app.eventLoop();
    return 0;
}
