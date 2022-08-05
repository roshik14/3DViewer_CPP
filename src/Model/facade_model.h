#ifndef SRC_MODEL_FACADE_MODEL_H_
#define SRC_MODEL_FACADE_MODEL_H_

#include <memory>
#include <type_traits>
#include <QString>
#include <QOpenGLWidget>

#include "../enums.h"
#include "../point.h"
#include "../object_settings.h"
#include "figure.h"
#include "file_reader.h"
#include "scene.h"
#include "settings.h"
#include "gif_maker.h"
#include "drawer.h"

namespace s21 {
class FacadeModel;
}

class s21::FacadeModel final {
 public:
    FacadeModel();
    void LoadObjectFromFile(const std::string &fileName);
    void Transform(const Point &p, SceneAction actionType);
    void RemoveFigure(int figure_index);
    void StartRecordGif();
    void SaveImage(const QString &fileName);
    void SaveGif(const QString &fileName);
    void AddFrameToGif();
    void SaveSettings(const ObjectSettings &objSettings);
    void SetDrawer(QOpenGLWidget *drawer);
    void UpdatePointsInDrawer();
    void UpdateSettingsInDrawer();
    // Getters
    int VerticesCount(int figure_index);
    int EdgeCount(int figure_index);
    int FiguresCount();
    std::string FigureName(int figure_index);
    ObjectSettings objectSettings();

 private:
    std::unique_ptr<AffineTransform> UpdateTransformType(SceneAction actionType);
    std::unique_ptr<FileReader> reader_;
    std::unique_ptr<Scene> scene_;
    std::unique_ptr<GifMaker> gifMaker_;
    std::unique_ptr<Settings> settings_;
    Drawer *drawer_;
    void SetPointsToFigure(std::unique_ptr<Figure> figure);
};

#endif  // SRC_MODEL_FACADE_MODEL_H_
