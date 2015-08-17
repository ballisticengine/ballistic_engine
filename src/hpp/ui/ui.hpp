#ifndef UI_HPP
#define	UI_HPP

#include <Rocket/Core.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/FileInterface.h>

#include "misc/singleton.hpp"
#include "config/Config.hpp"

using namespace Rocket::Core;
namespace RC = Rocket::Core;

class UI : public Singleton<UI> {
protected:
    RC::SystemInterface *system_interface;
    RC::RenderInterface *renderer_interface;
    RC::FileInterface *file_interface;
    
    RC::Context *context;
public:
    bool init(RC::SystemInterface *system_interface,
            RC::RenderInterface *renderer_interface,
            RC::FileInterface *file_interface);
    
    
    RC::Context *getContext();
    
    void showTestUi();
    
    ~UI();
};


#endif	

