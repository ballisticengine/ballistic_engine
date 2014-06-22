#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

class singleton {
protected:
    static singleton *instance;
    void *params;
    void setParams(void *params = 0);
public:

    static singleton *getInstance(void *params = 0);
};


#endif	/* SINGLETON_HPP */

