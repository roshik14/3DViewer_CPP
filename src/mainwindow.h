#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <memory>

#include "Controller/controller.h"
#include "command.h"
#include "enums.h"
#include "object_settings.h"
#include "point.h"
#include "settingswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
namespace s21 {
class MainWindow;
}
QT_END_NAMESPACE

class s21::MainWindow : public QMainWindow {
    Q_OBJECT
    using SlotPointer = void (s21::MainWindow::*)();

 public:
    explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();

 private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<QStringListModel> listModel_;
    std::shared_ptr<SettingsWindow> settingsWindow_;
    QStringList figureNames_;
    Controller *controller_;
    void Start();
    void ConnectSignals();
    void ConnectButtons();
    void ConnectActions(const QList<QAction *> &actions, SlotPointer);
    Point point();
    template <typename T>
    const QString senderName(QObject *obj);
    template <typename T>
    T CurrentAction(const QString &name);
    void ChangeActionStatus(const QList<QAction *> &actions, int index, bool status);
    void UpdateFigureInfo(int index);
    void UpdateFiguresList();
    void UpdateWindow();
    void OpenFile();
    void CloseFile();
    void SaveImage();
    void ChangeSettings();
    void StartRecordGif();
    void StopRecordGif();
    void EnableStartRecordAction();
    void EnableStopRecordAction();
    void SetFigureNames();
    void DrawFigure();

 private slots:
    void btnClicked();
    void actionHandler();
    void applySettingsHandler(const ObjectSettings &objSettings);
    void showSettingsWindow();
};

template <typename T>
const QString s21::MainWindow::senderName(QObject *obj) {
    auto widget = qobject_cast<T>(obj);
    if (widget) return widget->objectName();
    return "";
}

template <typename T>
T s21::MainWindow::CurrentAction(const QString &name) {
    if (name == "moveButton")
        return T::Move;
    else if (name == "rotateButton")
        return T::Rotate;
    return T::Scale;
}

#endif  // SRC_MAINWINDOW_H_
