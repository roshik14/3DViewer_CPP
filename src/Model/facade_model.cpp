#include "facade_model.h"
#include <QImage>
#include <QSize>
#include <clocale>

using s21::AffineTransform;
using s21::FacadeModel;
using s21::ObjectSettings;
using s21::Point;

FacadeModel::FacadeModel()
    : reader_(std::make_unique<FileReader>()),
      scene_(std::make_unique<Scene>()),
      gifMaker_(std::make_unique<GifMaker>()),
      settings_(std::make_unique<Settings>()),
      drawer_(nullptr) {
    std::setlocale(LC_ALL, "en_US.UTF-8");
}

void FacadeModel::LoadObjectFromFile(const std::string &fileName) {
    reader_->Read(fileName);
    auto figure = std::make_unique<Figure>();
    figure->SetName(fileName);
    SetPointsToFigure(std::move(figure));
    reader_->ClearData();
}

void FacadeModel::SetPointsToFigure(std::unique_ptr<Figure> figure) {
    figure->SetVertices(reader_->vertices());
    figure->SetVerticeNormals(reader_->verticeNormals());
    figure->SetVerticeTextures(reader_->verticeTextures());
    figure->SetFaces(reader_->faces());
    scene_->AddFigure(std::move(figure));
}

void FacadeModel::Transform(const Point &p, SceneAction actionType) {
    auto transformTypePtr = UpdateTransformType(actionType);
    scene_->TransformFigures(p, std::move(transformTypePtr));
}

void FacadeModel::SaveImage(const QString &fileName) {
    auto image = drawer_->grabFramebuffer();
    image.save(fileName);
}

void FacadeModel::StartRecordGif() { gifMaker_->StartRecord(drawer_->grabFramebuffer().size()); }

void FacadeModel::SaveGif(const QString &fileName) { gifMaker_->SaveGif(fileName); }

void FacadeModel::AddFrameToGif() {
    auto image = drawer_->grabFramebuffer();
    gifMaker_->AddFrame(image);
}

void FacadeModel::SaveSettings(const ObjectSettings &objSettings) { settings_->SetSettings(objSettings); }

std::unique_ptr<AffineTransform> FacadeModel::UpdateTransformType(SceneAction actionType) {
    switch (actionType) {
        case SceneAction::Move:
            return std::make_unique<AffineTranslate>(scene_->CenterPoint(0));
        case SceneAction::Rotate:
            return std::make_unique<AffineRotate>(scene_->CenterPoint(0));
        default:
            return std::make_unique<AffineScale>(scene_->CenterPoint(0));
    }
}

void FacadeModel::RemoveFigure(int figure_index) { scene_->RemoveFigure(figure_index); }

int FacadeModel::VerticesCount(int figure_index) { return scene_->VerticesCount(figure_index); }

int FacadeModel::EdgeCount(int figure_index) { return scene_->EdgeCount(figure_index); }

int FacadeModel::FiguresCount() { return scene_->FiguresCount(); }

std::string FacadeModel::FigureName(int figure_index) { return scene_->FigureName(figure_index); }

void FacadeModel::SetDrawer(QOpenGLWidget *drawer) { drawer_ = static_cast<Drawer *>(drawer); }

void FacadeModel::UpdatePointsInDrawer() {
    drawer_->SetVertices(scene_->PointsOfFigureWithIndex(0, Data::Vertex));
    drawer_->SetIndices(scene_->FacesOfFigureWithIndex(0, Data::SurfaceVertex));
    drawer_->UpdateScreen();
}

void FacadeModel::UpdateSettingsInDrawer() {
    drawer_->SetSettings(settings_->objectSettings());
    drawer_->UpdateScreen();
}

ObjectSettings FacadeModel::objectSettings() { return settings_->objectSettings(); }
