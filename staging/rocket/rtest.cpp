#include <Rocket/Core.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>

#include "ShellFileInterface.hpp"
#include "SystemInterfaceSDL2.hpp"
#include "RendererInterfaceSDL2.hpp"

#include <SDL2/SDL.h>

#include <GL/glew.h>

int main(int argc, char **argv)
{
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window * screen = SDL_CreateWindow("LibRocket SDL2 test", 20, 20, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glcontext = SDL_GL_CreateContext(screen);
    int oglIdx = -1;
    int nRD = SDL_GetNumRenderDrivers();
    for(int i=0; i<nRD; i++)
    {
        SDL_RendererInfo info;
        if(!SDL_GetRenderDriverInfo(i, &info))
        {
            if(!strcmp(info.name, "opengl"))
            {
                oglIdx = i;
            }
        }
    }
    SDL_Renderer * renderer = SDL_CreateRenderer(screen, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GLenum err = glewInit();

    if(err != GLEW_OK)
        fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 0, 1);
 
	RocketSDL2Renderer Renderer(renderer, screen);
	RocketSDL2SystemInterface SystemInterface;
	ShellFileInterface FileInterface("./assets/");

	Rocket::Core::SetFileInterface(&FileInterface);
	Rocket::Core::SetRenderInterface(&Renderer);
    Rocket::Core::SetSystemInterface(&SystemInterface);

	if(!Rocket::Core::Initialise())
		return 1;

	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

	Rocket::Core::Context *Context = Rocket::Core::CreateContext("default",
		Rocket::Core::Vector2i(640, 480));

	Rocket::Debugger::Initialise(Context);

	Rocket::Core::ElementDocument *Document = Context->LoadDocument("demo.rml");

	if(Document)
	{
		Document->Show();
		Document->RemoveReference();
		fprintf(stdout, "\nDocument loaded");
	}
	else
	{
		fprintf(stdout, "\nDocument is NULL");
	}

    bool done = false;

	while(!done)
	{
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

		Context->Render();
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEMOTION:
                    Context->ProcessMouseMove(event.motion.x, event.motion.y, SystemInterface.GetKeyModifiers());
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    Context->ProcessMouseButtonDown(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
                    break;

                case SDL_MOUSEBUTTONUP:
                    Context->ProcessMouseButtonUp(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
                    break;

                case SDL_MOUSEWHEEL:
                    Context->ProcessMouseWheel(event.wheel.y, SystemInterface.GetKeyModifiers());
                    break;

                case SDL_KEYDOWN:
                    Context->ProcessKeyDown(SystemInterface.TranslateKey(event.key.keysym.sym), SystemInterface.GetKeyModifiers());
                    break;
                default:
                    break;
            }
        }
        
		Context->Update();
	}

    Context->RemoveReference();
    Rocket::Core::Shutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

	return 0;
};
