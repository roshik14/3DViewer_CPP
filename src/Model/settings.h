#ifndef SRC_MODEL_SETTINGS_H_
#define SRC_MODEL_SETTINGS_H_

#include <QColor>
#include <QSettings>
#include <memory>

#include "../object_settings.h"

namespace s21 {
class Settings {
 public:
    Settings() :
         settings_(std::make_unique<QSettings>(".settings.ini", QSettings::NativeFormat)) {}
    void SetSettings(const ObjectSettings& objSettings) {
        settings_->setValue("projection_type", objSettings.projectionType);
        settings_->setValue("background_color", objSettings.backgroundColor);
        settings_->setValue("edge_color", objSettings.edgeColor);
        settings_->setValue("vertex_color", objSettings.vertexColor);
        settings_->setValue("line_type", objSettings.lineType);
        settings_->setValue("vertex_type", objSettings.vertexType);
        settings_->setValue("edge_size", objSettings.edgeSize);
        settings_->setValue("vertex_size", objSettings.vertexSize);
    }
    ObjectSettings objectSettings() {
        return ObjectSettings {
            settings_->value("background_color").value<QColor>(),
            settings_->value("edge_color").value<QColor>(),
            settings_->value("vertex_color").value<QColor>(),
            settings_->value("projection_type").toInt(),
            settings_->value("line_type").toInt(),
            settings_->value("vertex_type").toInt(),
            settings_->value("edge_size").toInt(),
            settings_->value("vertex_size").toInt()
        };
    }

 private:
    std::unique_ptr<QSettings> settings_;
};
}  // namespace s21

#endif  // SRC_MODEL_SETTINGS_H_
