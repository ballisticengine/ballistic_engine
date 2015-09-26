#ifndef UISIGNALDATA_HPP
#define	UISIGNALDATA_HPP

#include <string>
#include <map>
#include <Rocket/Core.h>

using namespace std;

class UISignalData {
    map<string, string> sigmap;
    Rocket::Core::ElementDocument *element;
public:
    void set(string k, string v);
    string get(string k);
};

#endif	

