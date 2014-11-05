#ifndef PYVECTOR_H
#define PYVECTOR_H
namespace bp = boost::python;
#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>
template<class T>
struct std_item
{
    typedef typename T::value_type V;
    static V& get(T  x, int i)
    {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) return x[i];
        IndexError();
    }
    static void set(T  x, int i, V const& v)
    {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) x[i]=v;
        else IndexError();
    }
    static void del(T  x, int i)
    {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) x.erase(i);
        else IndexError();
    }
    static void add(T const& x, V const& v)
    {
        x.push_back(v);
    }
};
void IndexError() { PyErr_SetString(PyExc_IndexError, "Index out of range"); }

#endif