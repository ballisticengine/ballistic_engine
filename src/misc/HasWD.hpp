#ifndef HASWD_HPP
#define	HASWD_HPP

#include <string>

using namespace std;

class HasWD {
protected:
     string wd;
public:
    HasWD();
    virtual ~HasWD();
    virtual void setWD(string wd);
    virtual string getWD();
};

#endif	/* HASWD_HPP */

