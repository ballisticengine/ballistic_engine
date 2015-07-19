#include "resources/exceptions.hpp"

 ResourceNotFound::ResourceNotFound(string file_name) : 
 file_name(file_name) {
     
 }

 const char* ResourceNotFound::what() const throw() {
     cout << "Requested resource " << file_name 
             << " doesn't exist" << endl;
 }