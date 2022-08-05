#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/facade_model.h"
#include "../enums.h"
#include "../object_settings.h"
#include "../point.h"
#include <QString>
#include <QOpenGLWidget>

namespace s21 {
class Controller;
}

class s21::Controller final {
 public:
    explicit Controller(FacadeModel *facade) : facade_(facade) {}
    void LoadObjectFromFile(const std::string &filename);
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
    std::string FigureName(int figure_index);
    int FiguresCount();
    ObjectSettings objectSettings();

 private:
    FacadeModel *facade_;
};

#endif  // SRC_CONTROLLER_CONTROLLER_H_
