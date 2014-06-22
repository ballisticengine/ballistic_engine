#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

class singleton {
protected:
    static singleton *instance;
public:
    singleton() {}
    static singleton *getInstance() {
        
        if (!singleton::instance) {
            singleton::instance = new singleton;
//            if (params) {
//                singleton::instance->setParams(params);
//            }

        }
        return singleton::instance;
    
    }
};


#endif	/* SINGLETON_HPP */

