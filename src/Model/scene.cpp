#include "scene.h"

#include <QDebug>

using s21::Point;
using s21::Scene;

void Scene::TransformFigures(const Point& p, AffinePointer transformPtr) {
    if (ContainsFigures()) {
        figures_[0]->TransformPoints(p, std::move(transformPtr));
    }
}

void Scene::AddFigure(std::unique_ptr<Figure> figure) {
    if (ContainsFigures()) figures_.pop_back();
    figures_.push_back(std::move(figure));
}

void Scene::RemoveFigure(int figure_index) {
    if (figure_index >= 0) figures_.erase(figures_.begin() + figure_index);
}

std::vector<Point> Scene::PointsOfFigureWithIndex(int figure_index, Data type) {
    std::vector<Point> result;
    if (ContainsFigures()) {
        if (type == Data::Vertex)
            result = figures_[figure_index]->vertices();
        else if (type == Data::VertexNormal)
            result = figures_[figure_index]->verticeNormals();
        else
            result = figures_[figure_index]->verticeTextures();
    }
    return result;
}

std::vector<std::vector<int>> Scene::FacesOfFigureWithIndex(int figure_index, Data type) {
    std::vector<std::vector<int>> result;
    if (ContainsFigures()) {
        if (type == Data::SurfaceVertex)
            result = figures_[figure_index]->surfaceVertices();
        else if (type == Data::SurfaceVertexNormal)
            result = figures_[figure_index]->surfaceNormals();
        else
            result = figures_[figure_index]->surfaceTextures();
    }
    return result;
}

inline bool Scene::ContainsFigures() { return !figures_.empty(); }

int Scene::VerticesCount(int figure_index) {
    return figure_index >= 0 ? figures_[figure_index]->VerticesCount() : 0;
}

int Scene::EdgeCount(int figure_index) { return figure_index >= 0 ? figures_[figure_index]->EdgeCount() : 0; }

int Scene::FiguresCount() { return figures_.size(); }

std::string Scene::FigureName(int figure_index) { return figures_[figure_index]->name(); }

Point* Scene::CenterPoint(int index) {
    if (ContainsFigures()) return figures_[index]->CenterPoint();
    return nullptr;
}
