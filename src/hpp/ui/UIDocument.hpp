#ifndef UIELEMENT_HPP
#define	UIELEMENT_HPP

#include <string>
#include <Rocket/Core.h>

using namespace Rocket::Core;
namespace RC = Rocket::Core;
using namespace std;

#include "ui/SignalListener.hpp"

class UIDocument {
protected:
    string file_name, name;
    RC::ElementDocument *document;
public:
    UIDocument(RC::ElementDocument *document, string file_name, string name);
    void setContentByID(string id, string content);
    void addEventListenerID(string id, string event, string signal);
    void show();
    void hide();


};


#endif

