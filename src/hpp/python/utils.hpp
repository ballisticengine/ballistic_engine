#ifndef PY_UTILS_HPP
#define	PY_UTILS_HPP

#include <map>
#include <string>
#include <boost/python.hpp>

/*
 * Source https://gist.github.com/octavifs/5362297
 */
 boost::python::dict toPythonDict(std::map<std::string, std::string> m);


#endif	

