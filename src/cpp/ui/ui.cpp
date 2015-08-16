#include "ui/ui.hpp"


  UI::UI(RC::SystemInterface *system_interface,
            RC::RenderInterface *renderer_interface,
            RC::FileInterface *file_interface) 
  : system_interface(system_interface), renderer_interface(renderer_interface), 
          file_interface(file_interface)
  {
      
  }


