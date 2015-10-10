#include "ModuleManager.hpp"

 void ModuleManager::registerModule(string name, void *class_instance) {
     modules[name]=class_instance;
 }

 void * ModuleManager::getModule(string name) {
     return modules[name];
 }
        
