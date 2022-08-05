#ifndef SRC_MODEL_SCENE_H_
#define SRC_MODEL_SCENE_H_

#include <memory>
#include "../enums.h"
#include "../point.h"
#include "affine_strategy.h"
#include "figure.h"

namespace s21 {
class Scene;
}

class s21::Scene final {
    using FigurePointer = std::unique_ptr<Figure>;
    using AffinePointer = std::unique_ptr<AffineTransform>;

 public:
    void TransformFigures(const Point& p, AffinePointer transformType);
    void AddFigure(FigurePointer figure);
    void RemoveFigure(int figure_index);
    // Getters
    std::vector<Point> PointsOfFigureWithIndex(int figure_index, Data type);
    std::vector<std::vector<int>> FacesOfFigureWithIndex(int figure_index, Data type);
    int VerticesCount(int figure_index);
    int EdgeCount(int figure_index);
    std::string FigureName(int figure_index);
    int FiguresCount();

    Point* CenterPoint(int index);

 private:
    bool ContainsFigures();
    std::vector<FigurePointer> figures_;
};

#endif  // SRC_MODEL_SCENE_H_
