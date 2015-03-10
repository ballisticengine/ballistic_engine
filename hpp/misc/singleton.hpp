#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

template <typename T>
class Singleton {
protected:
    
    void *params;
   
public:
    static T *getInstance() {
        static T i;
        return &i;
    
    }
  //  void setParams(void *params);
};


#endif	/* SINGLETON_HPP */

