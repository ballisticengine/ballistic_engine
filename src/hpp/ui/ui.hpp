#ifndef UI_HPP
#define	UI_HPP

#include <Rocket/Core.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/FileInterface.h>
#include <SDL2/SDL.h>

#include <string>

#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "renderer/RendererInterface.hpp"

#include "ui/librocket_interfaces/RendererInterfaceSDL2.hpp"
#include "ui/librocket_interfaces/SystemInterfaceSDL2.hpp"
#include "ui/librocket_interfaces/ShellFileInterface.hpp"

using namespace Rocket::Core;
namespace RC = Rocket::Core;

class UI : public Singleton<UI> {
protected:
    RocketSDL2SystemInterface *system_interface;
    RocketSDL2Renderer *rc_renderer_interface;
    ShellFileInterface *file_interface;
    RC::Context *context;
    RendererInterface *renderer;
public:
    bool init(RocketSDL2SystemInterface *system_interface,
            RocketSDL2Renderer *rc_renderer_interface,
            ShellFileInterface *file_interface,
            RendererInterface *renderer_interface
            );


    RC::Context *getContext();

    void showTestUi();
    void addElement(std::string file);
    void processSDLEvent(SDL_Event &event);

    ~UI();
};


#endif	

