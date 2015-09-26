#include "python/utils.hpp"

boost::python::dict toPythonDict(std::map<std::string, std::string> map) {
    std::map<std::string, std::string>::iterator iter;
	boost::python::dict dictionary;
	for (iter = map.begin(); iter != map.end(); ++iter) {
		dictionary[iter->first] = iter->second;
	}
	return dictionary;
}