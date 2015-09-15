#ifndef FORMSIGNALDATA_HPP
#define	FORMSIGNALDATA_HPP

#include <string>
#include <map>

using namespace std;

//change to more general UISignalData

class FormSignalData {
    map<string, string> sigmap;
public:
    void set(string k, string v);
    string get(string k);
};

#endif	

