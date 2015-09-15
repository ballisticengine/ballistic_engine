#include <Rocket/Core/Event.h>

#include "ui/FormSignalListener.hpp"

 FormSignalListener::FormSignalListener(string signal_name) : SignalListener(signal_name) {
     
 }

 
 void FormSignalListener::ProcessEvent(Rocket::Core::Event& event) {
     // {{0}} => params (json?)
     
     event.GetParameters();
     PyScripting::getInstance()->broadcast(signal_name, {0}, true);
 }