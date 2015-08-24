#ifndef SIGNALLISTENER_HPP
#define	SIGNALLISTENER_HPP

#include <string>
#include <iostream>
#include <Rocket/Core/EventListener.h>

using namespace std;

class SignalListener : public Rocket::Core::EventListener {
protected:
    string signal_name;
public:

    SignalListener(string signal_name);
    void ProcessEvent(Rocket::Core::Event& event);
};

#endif	

