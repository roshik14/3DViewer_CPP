#include "controller.h"

using s21::Controller;
using s21::ObjectSettings;
using s21::Point;

void Controller::Transform(const Point &p, SceneAction actionType) { facade_->Transform(p, actionType); }

void Controller::LoadObjectFromFile(const std::string &filename) { facade_->LoadObjectFromFile(filename); }

void Controller::RemoveFigure(int figure_index) { facade_->RemoveFigure(figure_index); }

void Controller::StartRecordGif() { facade_->StartRecordGif(); }

void Controller::SaveImage(const QString &fileName) { facade_->SaveImage(fileName); }

void Controller::SaveGif(const QString &fileName) { facade_->SaveGif(fileName); }

void Controller::AddFrameToGif() { facade_->AddFrameToGif(); }

void Controller::SaveSettings(const ObjectSettings &objSettings) { facade_->SaveSettings(objSettings); }

int Controller::VerticesCount(int figure_index) { return facade_->VerticesCount(figure_index); }

int Controller::EdgeCount(int figure_index) { return facade_->EdgeCount(figure_index); }

int Controller::FiguresCount() { return facade_->FiguresCount(); }

std::string Controller::FigureName(int figure_index) { return facade_->FigureName(figure_index); }

void Controller::SetDrawer(QOpenGLWidget *drawer) { facade_->SetDrawer(drawer); }

void Controller::UpdatePointsInDrawer() { facade_->UpdatePointsInDrawer(); }

void Controller::UpdateSettingsInDrawer() { facade_->UpdateSettingsInDrawer(); }

ObjectSettings Controller::objectSettings() { return facade_->objectSettings(); }
