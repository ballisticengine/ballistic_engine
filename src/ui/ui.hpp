#ifndef UI_HPP
#define	UI_HPP

#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/FileInterface.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Types.h>
#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <boost/thread/mutex.hpp>

#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "renderer/RendererInterface.hpp"
#include "ui/SignalListener.hpp"
#include "ui/UIDocument.hpp"

#include "ui/librocket_interfaces/Input.h"
#include "ui/librocket_interfaces/SystemInterfaceSDL2.hpp"
#include "ui/librocket_interfaces/ShellFileInterface.hpp"

using namespace Rocket::Core;
namespace RC = Rocket::Core;
using namespace std;

typedef vector<RC::Context *> context_vector;
//albo queue albo mutex
class UI : public Singleton<UI> {
protected:
    RocketSDL2SystemInterface *system_interface;
    Rocket::Core::RenderInterface *rc_renderer_interface;
    Rocket::Core::FileInterface *file_interface;
    RendererInterface *renderer;
    context_vector contexts;
    RC::Context * context;
    map<string, UIDocument *> docmap;
    
public:
    boost::mutex m;
    bool init(RocketSDL2SystemInterface *system_interface,
            Rocket::Core::RenderInterface *rc_renderer_interface,
            Rocket::Core::FileInterface *file_interface,
            RendererInterface *renderer_interface
            );


    RC::Context * getContext();
    void setContentByID(string id, string content);
    UIDocument * addDocument(string file, string name);
    UIDocument * getDocument(string name);
    void showDoc(string name);
    void addEventListenerID(string id, string event, string signal);
    void processSDLEvent(SDL_Event event);
    void showDebug(bool show);
    void cleanup();
};


#endif	

