#ifndef SRC_MODEL_AFFINE_STRATEGY_H_
#define SRC_MODEL_AFFINE_STRATEGY_H_

#include "../point.h"
#include "s21_matrix_oop.h"
namespace s21 {

class AffineTransform {
 public:
    virtual ~AffineTransform() {}
    virtual Point Transform(const Point &n, const Point &old) const = 0;

 protected:
    explicit AffineTransform(Point *const p) : center_point_(p) {}
    virtual Matrix CreateMatrix(const Point &p) const = 0;
    Point *const center_point_;
};

class AffineTranslate : public AffineTransform {
 public:
    explicit AffineTranslate(Point *const p) : AffineTransform(p) {}
    Point Transform(const Point &n, const Point &old) const override;

 private:
    Matrix CreateMatrix(const Point &p) const override;
};

class AffineRotate : public AffineTransform {
 public:
    explicit AffineRotate(Point *const p) : AffineTransform(p) {}
    Point Transform(const Point &n, const Point &old) const override;

 private:
    Matrix CreateMatrix(const Point &p) const override;
    Matrix CreateXMatrix(const double &x) const;
    Matrix CreateYMatrix(const double &y) const;
    Matrix CreateZMatrix(const double &z) const;
};

class AffineScale : public AffineTransform {
 public:
    explicit AffineScale(Point *const p) : AffineTransform(p) {}
    Point Transform(const Point &n, const Point &old) const override;

 private:
    Matrix CreateMatrix(const Point &p) const override;
};

}  // namespace s21

#endif  // SRC_MODEL_AFFINE_STRATEGY_H_
