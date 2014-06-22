#include "helpers/singleton.hpp"

singleton * singleton::instance=0;

singleton * singleton::getInstance(void *params)  {
        if (!singleton::instance) {
            singleton::instance = new singleton();
            if (params) {
                singleton::instance->setParams(params);
            }

        }
        return singleton::instance;
    }
        
