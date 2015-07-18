#ifndef RESOURCE_HPP
#define	RESOURCE_HPP

#include <string>

using namespace std;

class Resource {
protected:
    string filename, orig_filename;
public:
    virtual string getFilename();
    virtual string getOrigFilename();
    virtual void setFilename(string fn);
    virtual void setOrigFilename(string fn);
    Resource * getResource();
    
};

#endif	

