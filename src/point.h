#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include <iostream>
namespace s21 {
class Point final {
 public:
    Point(float x = 0.0, float y = 0.0, float z = 0.0) : x_(x), y_(y), z_(z) {}
    void print() { std::cout << x_ << ' ' << y_ << ' ' << z_ << std::endl; }
    Point& operator+=(const Point& p) {
        x_ += p.x_;
        y_ += p.y_;
        z_ += p.z_;
        return *this;
    }
    // Getters
    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }

 private:
    float x_;
    float y_;
    float z_;
};
}  // namespace s21

#endif  // SRC_POINT_H_
