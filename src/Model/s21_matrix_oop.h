#ifndef SRC_MODEL_S21_MATRIX_OOP_H_
#define SRC_MODEL_S21_MATRIX_OOP_H_

namespace s21 {
class Matrix;
}
class s21::Matrix {
 private:
    int _rows, _cols;
    float** _matrix;

 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
    int rows() const { return _rows; }
    int cols() const { return _cols; }
    bool eq_matrix(const Matrix& other);
    void sum_matrix(const Matrix& other);
    void sub_matrix(const Matrix& other);
    void mul_number(const float num);
    void mul_matrix(const Matrix& other);
    Matrix transpose();
    Matrix calc_complements();
    float determinant();
    Matrix inverse_matrix();
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    bool operator==(const Matrix& other);
    Matrix& operator=(const Matrix& other) noexcept;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const float num);
    float& operator()(int i, int j) const;
    void print();

 private:
    void create_matrix(int rows, int cols);
    inline bool is_empty_matrix(int rows, int cols);
    inline bool is_size_equal(const Matrix& m2);
    inline bool is_square_matrix(int rows, int cols);
    void copy_matrix(float** src, int rows, int cols);
    Matrix get_minor_matrix(const Matrix& m, int m_i, int m_j);
};

s21::Matrix operator*(const s21::Matrix& matrix, const float num);
s21::Matrix operator*(const float num, const s21::Matrix& other);

#endif  // SRC_MODEL_S21_MATRIX_OOP_H_
