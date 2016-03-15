#include "types/Matrix.hpp"

Matrix::Matrix(size_t cols, size_t rows) : cols(cols), rows(rows) {
    this->data = new scalar_t[cols * rows];
    memset(this->data, 0, cols*rows);
}

void Matrix::set(size_t col, size_t row, scalar_t value) {
    scalar_t **data = (scalar_t **)this->data;
    data[col][row] = value;
}

void Matrix::set(scalar_t *data) {
    this->data = data;
}

scalar_t Matrix::get(size_t col, size_t row) {
    scalar_t **data = (scalar_t **)this->data;
    return data[col][row];
}

scalar_t *Matrix::get() {
    return this->data;
}

Matrix::~Matrix() {
    delete this->data;
}

Matrix::operator scalar_t*() {
    return this->data;
}

//// Matrix4 ////

Matrix4::Matrix4() : Matrix(4, 4) {

}