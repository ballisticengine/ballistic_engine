#include <Rocket/Core/Event.h>
#include <Rocket/Core/Dictionary.h>
#include <Rocket/Core/Variant.h>

#include <Rocket/Core/Header.h>

#include "ui/FormSignalListener.hpp"

FormSignalListener::FormSignalListener(string signal_name) : SignalListener(signal_name) {

}

void FormSignalListener::ProcessEvent(Rocket::Core::Event& event) {
    const Rocket::Core::Dictionary *d = event.GetParameters();
    UISignalData *data = new UISignalData();
    Rocket::Core::String s;
    Rocket::Core::Variant *v;
    int n;
    while (d->Iterate(n, s, v)) {
        Rocket::Core::String val = v->Get<Rocket::Core::String>();
        data->set(string(s.CString()), string(val.CString()));        
    }

    PyScripting::getInstance()->broadcast(signal_name,{data}, true, true);
}