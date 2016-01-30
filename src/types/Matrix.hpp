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
    void set(size_t col, size_t row, scalar_t value);
    void set(scalar_t *data);
    scalar_t get(size_t col, size_t row);
    scalar_t *get();
    ~Matrix();
    operator scalar_t*();
};

#endif

