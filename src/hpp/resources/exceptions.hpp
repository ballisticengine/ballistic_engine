#ifndef EXCEPTIONS_HPP
#define	EXCEPTIONS_HPP

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class ResourceNotFound : public exception {
protected:
    string file_name;
public:
    ResourceNotFound(string file_name);
    virtual const char* what() const throw ();
    
    ~ResourceNotFound() throw () {
    }

};

#endif

