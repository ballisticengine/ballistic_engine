#ifndef FORMSIGNALLISTENER_HPP
#define	FORMSIGNALLISTENER_HPP

#include "ui/SignalListener.hpp"


class FormSignalListener : public SignalListener {
    public:
        FormSignalListener(string signal_name);
        void ProcessEvent(Rocket::Core::Event& event);
};


#endif	

