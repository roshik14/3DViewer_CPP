#ifndef SRC_SETTINGSWINDOW_H_
#define SRC_SETTINGSWINDOW_H_

#include <QWidget>
#include <QColor>
#include <memory>

#include "object_settings.h"

namespace s21 {
class SettingsWindow;
}
namespace Ui {
class SettingsWindow;
}

class s21::SettingsWindow : public QWidget {
    Q_OBJECT

 public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void setValues(const ObjectSettings &objSettings);

 signals:
    void apply(const ObjectSettings &objSettings);

 private:
    std::unique_ptr<Ui::SettingsWindow> ui;
    QColor backgroundColor_;
    QColor edgeColor_;
    QColor verticeColor_;
    void ConnectSignals();
    QColor GetChoosenColor(const QColor &defaultColor);

 private slots:
    void applyBtnClicked();
    void colorBtnClicked();
};

#endif  // SRC_SETTINGSWINDOW_H_
