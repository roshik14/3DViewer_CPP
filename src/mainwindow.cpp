#include "mainwindow.h"

// #include <QGLWidget>
#include <QTimer>
#include <QtOpenGL>
#include <QFileDialog>
#include <cmath>

#include "ui_mainwindow.h"

using s21::Controller;
using s21::MainWindow;

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      ui(std::make_unique<Ui::MainWindow>()),
      listModel_(std::make_unique<QStringListModel>()),
      settingsWindow_(std::make_shared<SettingsWindow>()),
      controller_(controller) {
    ui->setupUi(this);
    Start();
}

MainWindow::~MainWindow() {}

inline void MainWindow::Start() {
    ConnectSignals();
    ChangeActionStatus(ui->menuGif->actions(), 1, false);
    controller_->SetDrawer(ui->openGLWidget);
    controller_->UpdateSettingsInDrawer();
}

void MainWindow::ConnectSignals() {
    ConnectActions(ui->menuFile->actions(), &MainWindow::actionHandler);
    ConnectActions(ui->menuGif->actions(), &MainWindow::actionHandler);
    ConnectActions(ui->menuSettings->actions(), &MainWindow::actionHandler);
    ConnectButtons();
    connect(settingsWindow_.get(), &SettingsWindow::apply, this, &MainWindow::applySettingsHandler);
}

inline void MainWindow::ConnectButtons() {
    connect(ui->moveButton, &QPushButton::clicked, this, &MainWindow::btnClicked);
    connect(ui->scaleButton, &QPushButton::clicked, this, &MainWindow::btnClicked);
    connect(ui->rotateButton, &QPushButton::clicked, this, &MainWindow::btnClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::showSettingsWindow);
}

void MainWindow::btnClicked() {
    auto name = senderName<QPushButton *>(QObject::sender());
    SceneAction action = CurrentAction<SceneAction>(name);
    Point p = point();
    std::make_unique<TransformSceneCommand>(controller_, p, action)->Execute();
    DrawFigure();
}

void MainWindow::ConnectActions(const QList<QAction *> &actions, SlotPointer pointer) {
    for (auto i = 0; i < actions.size(); ++i) connect(actions[i], &QAction::triggered, this, pointer);
}

void MainWindow::actionHandler() {
    auto name = senderName<QAction *>(QObject::sender());
    if (name == "actionOpen") {
        OpenFile();
    } else if (name == "actionImage") {
        SaveImage();
    } else if (name == "actionStartGif") {
        StartRecordGif();
    } else if (name == "actionStopGif") {
        StopRecordGif();
    } else if (name == "actionClose") {
        CloseFile();
    } else if (name == "actionChangeSettings") {
        ChangeSettings();
    }
}

inline void MainWindow::OpenFile() {
    std::make_unique<OpenFileCommand>(controller_)->Execute();
    DrawFigure();
    UpdateWindow();
}

inline void MainWindow::CloseFile() {
    std::make_unique<CloseFileCommand>(controller_, ui->listView->currentIndex().row())->Execute();
    DrawFigure();
    UpdateWindow();
}

inline void MainWindow::SaveImage() { std::make_unique<SaveImageCommand>(controller_, this)->Execute(); }

inline void MainWindow::ChangeSettings() {
    std::make_unique<OpenSettingsWindowCommand>(controller_, settingsWindow_)->Execute();
}

inline void MainWindow::StartRecordGif() {
    std::make_unique<StartRecordGifCommand>(controller_)->Execute();
    EnableStopRecordAction();
}

inline void MainWindow::StopRecordGif() {
    std::make_unique<StopRecordGifCommand>(controller_)->Execute();
    EnableStartRecordAction();
}

inline void MainWindow::EnableStopRecordAction() {
    ChangeActionStatus(ui->menuGif->actions(), 0, false);
    ChangeActionStatus(ui->menuGif->actions(), 1, true);
}

inline void MainWindow::EnableStartRecordAction() {
    ChangeActionStatus(ui->menuGif->actions(), 0, true);
    ChangeActionStatus(ui->menuGif->actions(), 1, false);
}

inline void MainWindow::ChangeActionStatus(const QList<QAction *> &actions, int index, bool status) {
    actions.at(index)->setEnabled(status);
}

inline void MainWindow::UpdateWindow() {
    SetFigureNames();
    UpdateFiguresList();
    UpdateFigureInfo(figureNames_.size() - 1);
}

inline void MainWindow::showSettingsWindow() {
    std::make_unique<OpenSettingsWindowCommand>(controller_, settingsWindow_)->Execute();
}

inline void MainWindow::applySettingsHandler(const ObjectSettings &objSettings) {
    std::make_unique<SaveSettingsCommand>(controller_, objSettings)->Execute();
}

inline void MainWindow::UpdateFigureInfo(int index) {
    ui->vertCount->setValue(controller_->VerticesCount(index));
    ui->edgeCount->setValue(controller_->EdgeCount(index));
}

inline void MainWindow::UpdateFiguresList() {
    listModel_->setStringList(figureNames_);
    ui->listView->setModel(listModel_.get());
}

inline s21::Point MainWindow::point() {
    return Point(ui->inputX->value(), ui->inputY->value(), ui->inputZ->value());
}

void MainWindow::SetFigureNames() {
    figureNames_.clear();
    auto figuresCount = controller_->FiguresCount();
    for (auto i = 0; i < figuresCount; ++i)
        figureNames_ << QString::fromStdString(controller_->FigureName(i));
}

inline void MainWindow::DrawFigure() {
    controller_->UpdatePointsInDrawer();
    controller_->AddFrameToGif();
}
