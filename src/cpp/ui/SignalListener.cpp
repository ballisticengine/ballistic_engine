#include "ui/SignalListener.hpp"

SignalListener::SignalListener(string signal_name) {
    this->signal_name = signal_name;
}

void SignalListener::ProcessEvent(Rocket::Core::Event& event) {
    cout << "-------------Invoke " << signal_name << endl;
}