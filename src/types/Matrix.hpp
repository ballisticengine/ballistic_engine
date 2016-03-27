#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstring>
#include "types/basic_typedefs.hpp"

using namespace std;

class Matrix {
protected:
    size_t cols, rows;
    scalar_t *data;
public:
    Matrix(size_t cols, size_t rows);
    virtual void set(size_t col, size_t row, scalar_t value);
    virtual void set(scalar_t *data);
    virtual scalar_t get(size_t col, size_t row);
    virtual scalar_t *get();
    virtual Matrix & operator*(Matrix &matrix);
    virtual  ~Matrix();
    virtual operator scalar_t*();
};

class Matrix4 : public Matrix {
public:
    Matrix4();
};

#endif

