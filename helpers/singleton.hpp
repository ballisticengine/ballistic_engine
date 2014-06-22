#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

class singleton {
protected:
    static singleton *instance;
    void *params;
    void setParams(void *params = 0);
public:

    static singleton *getInstance(void *params = 0) {
        if (!singleton::instance) {
            singleton::instance = new singleton();
            if (params) {
                singleton::instance->setParams(params);
            }

        }
        return singleton::instance;
    }
};


#endif	/* SINGLETON_HPP */

