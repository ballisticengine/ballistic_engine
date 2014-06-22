#ifndef FACTORY_HPP
#define	FACTORY_HPP

#include <map>
#include <string>

using namespace std;


class factory {
protected:
    map <string,void *> items;
public:
    factory();
    void * get(const string &item);
};

#endif	/* FACTORY_HPP */

