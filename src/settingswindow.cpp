#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QColorDialog>

using s21::SettingsWindow;

SettingsWindow::SettingsWindow(QWidget *parent) :
        QWidget(parent),
        ui(std::make_unique<Ui::SettingsWindow>()) {
    ui->setupUi(this);
    ConnectSignals();
}

SettingsWindow::~SettingsWindow() {
}

void SettingsWindow::ConnectSignals() {
    connect(ui->applyButton, &QPushButton::clicked, this, &SettingsWindow::applyBtnClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsWindow::close);
    connect(ui->edgeColorBtn, &QPushButton::clicked, this, &SettingsWindow::colorBtnClicked);
    connect(ui->backgroundColorBtn, &QPushButton::clicked, this, &SettingsWindow::colorBtnClicked);
    connect(ui->vertexColorBtn, &QPushButton::clicked, this, &SettingsWindow::colorBtnClicked);
}

void SettingsWindow::setValues(const ObjectSettings &settings) {
    ui->projectionType->setCurrentIndex(settings.projectionType);
    ui->lineType->setCurrentIndex(settings.lineType);
    ui->vertexType->setCurrentIndex(settings.vertexType);
    ui->edgeThickness->setValue(settings.edgeSize);
    ui->vertexSize->setValue(settings.vertexSize);
    backgroundColor_.setRgb(settings.backgroundColor.rgb());
    edgeColor_.setRgb(settings.edgeColor.rgb());
    verticeColor_.setRgb(settings.vertexColor.rgb());
}

void SettingsWindow::applyBtnClicked() {
    ObjectSettings objSettings {
        backgroundColor_,
        edgeColor_,
        verticeColor_,
        ui->projectionType->currentIndex(),
        ui->lineType->currentIndex(),
        ui->vertexType->currentIndex(),
        ui->edgeThickness->value(),
        ui->vertexSize->value()
    };
    close();
    emit apply(objSettings);
}

QColor SettingsWindow::GetChoosenColor(const QColor &defaultColor) {
    auto color = QColorDialog::getColor(defaultColor, this, "Choose color");
    return color.isValid() ? color : defaultColor;
}

void SettingsWindow::colorBtnClicked() {
    const QString &name = QObject::sender()->objectName();
    if (name == "edgeColorBtn")
        edgeColor_.setRgb(GetChoosenColor(edgeColor_).rgb());
    else if (name == "backgroundColorBtn")
        backgroundColor_.setRgb(GetChoosenColor(backgroundColor_).rgb());
    else if (name == "vertexColorBtn")
        verticeColor_.setRgb(GetChoosenColor(verticeColor_).rgb());
}
