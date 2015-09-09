#ifndef UIELEMENT_HPP
#define	UIELEMENT_HPP

#include <string>
#include <vector>
#include <Rocket/Core.h>

using namespace Rocket::Core;
namespace RC = Rocket::Core;
using namespace std;

#include "ui/SignalListener.hpp"

class UIDocument {
protected:
    string file_name, name;
    RC::ElementDocument *document;
    void getElements(
            ElementList& elements,
            string selector,
            RC::ElementDocument *root = 0
            );
    vector<SignalListener *> listeners;
public:
    UIDocument(RC::ElementDocument *document, string file_name, string name);
    ~UIDocument();
    void setContent(string id, string content);
    void addEventListener(string id, string event, string signal);
    void getElements(string selector, ElementList & elements);
    void show();
    void hide();


};


#endif

