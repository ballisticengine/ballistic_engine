#ifndef MODULEMANAGER_HPP
#define	MODULEMANAGER_HPP


#include <string>
#include <map>
#include "misc/singleton.hpp"

using namespace std;

class ModuleManager : public Singleton<ModuleManager> {
    protected:
        map<string, void *> modules;
    public:
        void registerModule(string name, void *class_instance);
        void *getModule(string name);
};

#endif

