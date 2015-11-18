#ifndef SCRIPT_HPP
#define	SCRIPT_HPP

#include <string>
#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include "python/ScriptBase.hpp"

using namespace std;
namespace bp = boost::python;

class Script : public ScriptBase {
    public:
          Script(string filename);
          virtual void run();
};

#endif