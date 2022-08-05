#include "s21_matrix_oop.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

using s21::Matrix;

const float eps = 1e-7;

void Matrix::create_matrix(int rows, int cols) {
    _matrix = new float*[rows];
    _matrix[0] = new float[rows * cols]();
    for (int i = 1; i < rows; i++) {
        _matrix[i] = _matrix[i - 1] + cols;
    }
}

inline bool Matrix::is_empty_matrix(int rows, int cols) { return rows == 0 || cols == 0; }

inline bool Matrix::is_size_equal(const Matrix& m2) { return _rows == m2._rows && _cols == m2._cols; }

inline bool Matrix::is_square_matrix(int rows, int cols) { return rows == cols; }

void Matrix::copy_matrix(float** src, int rows, int cols) {
    create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            _matrix[i][j] = src[i][j];
        }
    }
}

Matrix Matrix::get_minor_matrix(const Matrix& m, int m_i, int m_j) {
    int rows = m.rows();
    int cols = m.cols();
    Matrix result(rows - 1, cols - 1);
    for (int i = 0, res_i = 0; i < rows; i++) {
        if (i != m_i) {
            for (int j = 0, res_j = 0; j < cols; j++) {
                if (j != m_j) result(res_i, res_j++) = m(i, j);
            }
            res_i++;
        }
    }
    return result;
}

Matrix::Matrix() : _rows(0), _cols(0), _matrix(nullptr) {}

Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    if (is_empty_matrix(rows, cols)) throw std::invalid_argument("Rows or columns can't be less or equal 0");
    create_matrix(rows, cols);
}

Matrix::Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols) {
    copy_matrix(other._matrix, this->_rows, this->_cols);
}

Matrix::Matrix(Matrix&& other) : _rows(other._rows), _cols(other._cols) {
    copy_matrix(other._matrix, this->_rows, this->_cols);
    delete[] other._matrix[0];
    delete[] other._matrix;
    other._rows = 0;
    other._cols = 0;
}

Matrix::~Matrix() {
    if (this->_rows) {
        delete[] this->_matrix[0];
        delete[] this->_matrix;
    }
}

bool Matrix::eq_matrix(const Matrix& other) {
    bool result = true;
    if (!is_size_equal(other)) {
        result = false;
    } else {
        for (int i = 0; i < this->_rows; i++) {
            for (int j = 0; j < this->_cols; j++) {
                if (fabs(this->_matrix[i][j] - other._matrix[i][j]) >= eps) result = false;
            }
        }
    }
    return result;
}

void Matrix::sum_matrix(const Matrix& other) {
    if (!is_size_equal(other)) throw std::logic_error("Matrixes sizes are not equal");
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) this->_matrix[i][j] += other._matrix[i][j];
    }
}

void Matrix::sub_matrix(const Matrix& other) {
    if (!is_size_equal(other)) throw std::logic_error("Matrixes sizes are not equal");
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            this->_matrix[i][j] -= other._matrix[i][j];
        }
    }
}

void Matrix::mul_number(const float num) {
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            this->_matrix[i][j] *= num;
        }
    }
}

void Matrix::mul_matrix(const Matrix& other) {
    if (this->_cols != other._rows) throw std::logic_error("Can't mul matrixes");
    Matrix result(this->_rows, other._cols);
    for (int i = 0; i < result._rows; i++) {
        for (int j = 0; j < result._cols; j++) {
            for (int k = 0; k < other._rows; k++)
                result._matrix[i][j] += this->_matrix[i][k] * other._matrix[k][j];
        }
    }
    *this = result;
}

Matrix Matrix::transpose() {
    Matrix result(this->_cols, this->_rows);
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            result._matrix[j][i] = this->_matrix[i][j];
        }
    }
    return result;
}

float Matrix::determinant() {
    float result = 0;
    if (!is_square_matrix(this->_rows, this->_cols)) throw std::logic_error("Matrix isn't square matrix");
    if (_rows == 1) {
        result = (*this)(0, 0);
    } else if (_rows == 2) {
        result = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
    } else {
        for (int i = 0; i < _rows; i++) {
            Matrix minor = get_minor_matrix(*this, 0, i);
            result += pow(-1, i + 2) * (*this)(0, i) * minor.determinant();
        }
    }
    return result;
}

Matrix Matrix::calc_complements() {
    if (!is_square_matrix(this->_rows, this->_cols)) throw std::logic_error("Matrix isn't square matrix");
    Matrix result(this->_rows, this->_cols);
    if (this->_rows == 1) {
        result(0, 0) = 1;
    } else {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                Matrix minor = get_minor_matrix(*this, i, j);
                result(i, j) = pow(-1, i + j + 2) * minor.determinant();
            }
        }
    }
    return result;
}

Matrix Matrix::inverse_matrix() {
    float det = this->determinant();
    if (det == 0.0) throw std::invalid_argument("Determinant is 0");
    Matrix calc = this->calc_complements();
    Matrix transposed = calc.transpose();
    transposed.mul_number(1 / det);
    return transposed;
}

Matrix Matrix::operator+(const Matrix& other) {
    Matrix result(*this);
    result.sum_matrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix& other) {
    Matrix result(*this);
    result.sub_matrix(other);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {
    Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

bool Matrix::operator==(const Matrix& other) { return this->eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) noexcept {
    this->_rows = other._rows;
    this->_cols = other._cols;
    delete[] this->_matrix[0];
    delete[] this->_matrix;
    create_matrix(this->_rows, this->_cols);
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) this->_matrix[i][j] = other._matrix[i][j];
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    this->sum_matrix(other);
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    this->sub_matrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    this->mul_matrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const float num) {
    this->mul_number(num);
    return *this;
}

float& Matrix::operator()(int i, int j) const {
    if ((i < 0 || i > _rows) || (j < 0 || j > _cols)) throw std::out_of_range("Outside of matrix");
    return this->_matrix[i][j];
}

Matrix operator*(const float num, const Matrix& other) {
    Matrix result(other);
    result *= num;
    return result;
}

Matrix operator*(const Matrix& other, const float num) {
    Matrix result(other);
    result *= num;
    return result;
}

void Matrix::print() {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
