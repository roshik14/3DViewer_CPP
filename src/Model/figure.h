#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include <algorithm>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "../enums.h"
#include "../point.h"
#include "affine_strategy.h"
#include "surface.h"

namespace s21 {
class Figure;
}

class s21::Figure final {
    using Points = std::vector<Point>;
    using Surfaces = std::vector<Surface>;
    using AffinePointer = std::unique_ptr<AffineTransform>;

 public:
    void TransformPoints(const Point &p, AffinePointer transform);
    void printVertices();
    void printNormals();
    void printTextures();
    void printSurfaces();

    void SetVertices(Points &&points) noexcept;
    void SetVerticeNormals(Points &&points) noexcept;
    void SetVerticeTextures(Points &&points) noexcept;
    void SetFaces(Surfaces &&surfaces) noexcept;
    void SetName(const std::string &name);
    // Getters
    Points vertices();
    Points verticeNormals();
    Points verticeTextures();
    std::vector<std::vector<int>> surfaceVertices();
    std::vector<std::vector<int>> surfaceNormals();
    std::vector<std::vector<int>> surfaceTextures();
    int VerticesCount();
    int EdgeCount();
    int FiguresCount();
    std::string name();

    Point *CenterPoint();

 private:
    enum class FaceType { V, VT, VN };
    Point center_point;
    Points vertices_;
    Points verticeNormals_;
    Points verticeTextures_;
    Surfaces faces_;
    std::string name_;

    void printPoint(const Point &p);
    void printSurfaceVertexes();
    void printSurfaceNormals();
    void printSurfaceTextures();
    std::vector<std::vector<int>> ConvertSurfaceContainer(FaceType type);
    std::pair<int, int> EdgePair(int a, int b);
};
#endif  // SRC_MODEL_FIGURE_H_
