#include <Rocket/Core/Event.h>
#include <Rocket/Core/Dictionary.h>
#include <Rocket/Core/Variant.h>

#include <Rocket/Core/Header.h>

#include "ui/FormSignalListener.hpp"

FormSignalListener::FormSignalListener(string signal_name) : SignalListener(signal_name) {

}

void FormSignalListener::ProcessEvent(Rocket::Core::Event& event) {
    // {{0}} => params (json?)

    const Rocket::Core::Dictionary *d = event.GetParameters();
    FormSignalData *data = new FormSignalData();
    cout << "Dict" << endl;
    //bool Iterate(int &pos, String& key, Variant* &value) const;
    Rocket::Core::String s;
    Rocket::Core::Variant *v;
    int n;
    while (d->Iterate(n, s, v)) {
        Rocket::Core::String val = v->Get<Rocket::Core::String>();
        data->set(string(s.CString()), string(val.CString()));
        cout << s.CString() << "=" << val.CString() << "---" << endl;
    }

    PyScripting::getInstance()->broadcast(signal_name,{data}, true, true);
}