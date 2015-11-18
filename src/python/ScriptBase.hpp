#ifndef SCRIPTBASE_HPP
#define	SCRIPTBASE_HPP

#include <string>
#include <boost/python.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace bp = boost::python;

class ScriptBase {
    protected:
        char * code;
        string filename;
        bp::object module;
    public:
        ScriptBase(string filename);
        virtual ~ScriptBase();
        virtual const char * const getCode();
};

#endif