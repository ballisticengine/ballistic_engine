#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

class singleton {
protected:
    static singleton *instance;
    void *params;
public:
    singleton() {}
    static singleton *getInstance() {
        
        if (!singleton::instance) {
            singleton::instance = new singleton;
//              if (params) {
//               singleton::instance->setParams(params);
//            }

        }
        return singleton::instance;
    
    }
  //  void setParams(void *params);
};


#endif	/* SINGLETON_HPP */

