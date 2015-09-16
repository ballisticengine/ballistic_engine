#ifndef UISIGNALDATA_HPP
#define	UISIGNALDATA_HPP

#include <string>
#include <map>

using namespace std;

class UISignalData {
    map<string, string> sigmap;
public:
    void set(string k, string v);
    string get(string k);
};

#endif	

