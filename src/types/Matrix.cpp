#include "types/Matrix.hpp"

Matrix::Matrix(size_t cols, size_t rows) : cols(cols), rows(rows) {
    this->data = new scalar_t[cols * rows];
}

void Matrix::set(size_t col, size_t row, scalar_t value) {
    //this->data[col][row]=data;
}

void Matrix::set(scalar_t *data) {
    this->data = data;
}

scalar_t Matrix::get(size_t col, size_t row) {
    //return this->data[col][row];
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