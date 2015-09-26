#include "ui/SignalListener.hpp"

SignalListener::SignalListener(string signal_name) {
    this->signal_name = signal_name;
}

void SignalListener::ProcessEvent(Rocket::Core::Event& event) {
    PyScripting::getInstance()->broadcast(signal_name, {0}, true);
}