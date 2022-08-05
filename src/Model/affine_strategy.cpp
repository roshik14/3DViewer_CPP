#include "affine_strategy.h"
#include <cmath>

using s21::AffineRotate;
using s21::AffineScale;
using s21::AffineTranslate;
using s21::Matrix;
using s21::Point;

namespace {
Matrix CreateTranslateMatrix(const Point &p) {
    Matrix matrix(4, 4);
    for (auto i = 0; i < matrix.rows(); ++i) {
        matrix(i, i) = 1.0;
    }
    matrix(0, 3) = p.x();
    matrix(1, 3) = p.y();
    matrix(2, 3) = p.z();
    return matrix;
}

Matrix CreatePointVector(const Point &p) {
    Matrix m(4, 1);
    m(0, 0) = p.x();
    m(1, 0) = p.y();
    m(2, 0) = p.z();
    m(3, 0) = 1.0;
    return m;
}
}  // namespace

Point AffineTranslate::Transform(const Point &n, const Point &old) const {
    auto matrix = CreateMatrix(n) * CreatePointVector(old);
    return Point{matrix(0, 0), matrix(1, 0), matrix(2, 0)};
}

Matrix AffineTranslate::CreateMatrix(const Point &p) const { return CreateTranslateMatrix(p); }

Point AffineRotate::Transform(const Point &n, const Point &old) const {
    auto matrix = CreateMatrix(n) * CreatePointVector(old);
    return Point{matrix(0, 0), matrix(1, 0), matrix(2, 0)};
}

Matrix AffineRotate::CreateMatrix(const Point &p) const {
    if (center_point_) {
        auto translateMatrix = CreateTranslateMatrix(*center_point_);
        auto negativeTranslateMatrix =
            CreateTranslateMatrix(Point(-center_point_->x(), -center_point_->y(), -center_point_->z()));
        auto pointMatrix = CreateXMatrix(p.x()) * CreateYMatrix(p.y()) * CreateZMatrix(p.z());
        return translateMatrix * pointMatrix * negativeTranslateMatrix;
    }
    return Matrix{};
}

Matrix AffineRotate::CreateXMatrix(const double &x) const {
    Matrix matrix(4, 4);
    matrix(0, 0) = 1.0;
    matrix(1, 1) = cos(x);
    matrix(1, 2) = sin(x);
    matrix(2, 1) = sin(x) * -1;
    matrix(2, 2) = cos(x);
    matrix(3, 3) = 1.0;
    return matrix;
}

Matrix AffineRotate::CreateYMatrix(const double &y) const {
    Matrix matrix(4, 4);
    matrix(0, 0) = cos(y);
    matrix(0, 2) = sin(y) * -1;
    matrix(1, 1) = 1;
    matrix(2, 0) = sin(y);
    matrix(2, 2) = cos(y);
    matrix(3, 3) = 1;
    return matrix;
}

Matrix AffineRotate::CreateZMatrix(const double &z) const {
    Matrix matrix(4, 4);
    matrix(0, 0) = cos(z);
    matrix(0, 1) = sin(z);
    matrix(1, 0) = sin(z) * -1;
    matrix(1, 1) = cos(z);
    matrix(2, 2) = 1;
    matrix(3, 3) = 1;
    return matrix;
}

Point AffineScale::Transform(const Point &n, const Point &old) const {
    auto matrix = CreateMatrix(n) * CreatePointVector(old);
    return Point{matrix(0, 0), matrix(1, 0), matrix(2, 0)};
}

Matrix AffineScale::CreateMatrix(const Point &p) const {
    Matrix matrix(4, 4);
    matrix(0, 0) = p.x();
    matrix(1, 1) = p.y();
    matrix(2, 2) = p.z();
    matrix(3, 3) = 1.0;
    return matrix;
}
