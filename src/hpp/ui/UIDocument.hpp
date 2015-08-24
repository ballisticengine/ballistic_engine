#ifndef UIELEMENT_HPP
#define	UIELEMENT_HPP

#include <string>
#include <Rocket/Core.h>

using namespace Rocket::Core;
namespace RC = Rocket::Core;
using namespace std;

class UIDocument {
protected:
    RC::Context * context;
    string file_name;
public:
    UIDocument(string file_name);
    RC::Context * getContext();
    void setContentByID(string id, string content);
    void show();
    void hide();
    

};


#endif

