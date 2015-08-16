#ifndef UI_HPP
#define	UI_HPP

#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/FileInterface.h>

#include "misc/singleton.hpp"

using namespace Rocket::Core;
namespace RC = Rocket::Core;

class UI : public Singleton<UI> {
protected:
    RC::SystemInterface *system_interface;
    RC::RenderInterface *renderer_interface;
    RC::FileInterface *file_interface;
public:
    UI(RC::SystemInterface *system_interface,
            RC::RenderInterface *renderer_interface,
            RC::FileInterface *file_interface);
    ~UI();
};


#endif	

