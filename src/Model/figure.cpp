#include "figure.h"

#include <QDebug>

using s21::Figure;
using s21::Point;

void Figure::TransformPoints(const Point &p, AffinePointer transf) {
    for (auto itb = vertices_.begin(), ite = vertices_.end(); itb != ite; ++itb) {
        *itb = transf->Transform(p, *itb);
    }
    auto ptr = transf.get();
    if (ptr) {
        auto &obj = *ptr;
        if (typeid(AffineTranslate).name() == typeid(obj).name()) {
            center_point += p;
        }
    }
}

std::vector<Point> Figure::vertices() { return vertices_; }

std::vector<Point> Figure::verticeNormals() { return verticeNormals_; }

std::vector<Point> Figure::verticeTextures() { return verticeTextures_; }

std::vector<std::vector<int>> Figure::surfaceVertices() { return ConvertSurfaceContainer(FaceType::V); }

std::vector<std::vector<int>> Figure::surfaceNormals() { return ConvertSurfaceContainer(FaceType::VN); }

std::vector<std::vector<int>> Figure::surfaceTextures() { return ConvertSurfaceContainer(FaceType::VT); }

void Figure::SetVertices(Points &&points) noexcept { vertices_ = std::move(points); }

void Figure::SetVerticeNormals(Points &&points) noexcept { verticeNormals_ = std::move(points); }

void Figure::SetVerticeTextures(Points &&points) noexcept { verticeTextures_ = std::move(points); }

void Figure::SetFaces(Surfaces &&surfaces) noexcept { faces_ = std::move(surfaces); }

void Figure::SetName(const std::string &name) {
    int slashIndex = name.find_last_of('/') + 1;
    for (size_t i = slashIndex; i < name.size(); ++i) {
        name_ += name[i];
    }
}

std::vector<std::vector<int>> Figure::ConvertSurfaceContainer(FaceType type) {
    std::vector<std::vector<int>> result;
    for (auto itb = faces_.begin(), ite = faces_.end(); itb != ite; ++itb) {
        if (type == FaceType::V)
            result.push_back(itb->vertices());
        else if (type == FaceType::VT)
            result.push_back(itb->verticeNormals());
        else
            result.push_back(itb->verticeTextures());
    }
    return result;
}

int Figure::VerticesCount() { return vertices_.size(); }

int Figure::EdgeCount() {
    std::set<std::pair<int, int>> edges;
    for (auto it = faces_.begin(), ite = faces_.end(); it != ite; ++it) {
        auto vs = it->vertices();
        for (size_t i = 0, end = vs.size() - 1; i < end; i += 2) {
            edges.insert(EdgePair(vs[i], vs[i + 1]));
        }
        edges.insert(EdgePair(vs.back(), vs[0]));
    }
    return edges.size();
}

std::pair<int, int> Figure::EdgePair(int a, int b) {
    auto max = std::max(a, b);
    auto min = std::min(a, b);
    return std::pair<int, int>{min, max};
}

std::string Figure::name() { return name_; }

Point *Figure::CenterPoint() { return &center_point; }
