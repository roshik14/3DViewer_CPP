#include "command.h"
#include <QByteArray>
#include <QFileDialog>
#include <QImageReader>

void s21::OpenFileCommand::Execute() {
    auto name = QFileDialog::getOpenFileName(nullptr,
                QObject::tr("Open File"),
                "./",
                QObject::tr("Text files(*.obj)"));
    if (!name.isEmpty()) {
        controller_->LoadObjectFromFile(name.toStdString());
    }
}

void s21::SaveImageCommand::Execute() {
    auto fileDialog = new QFileDialog(parent_, QObject::tr("Save image"), "./");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setMimeTypeFilters(GetSupportedImageTypes());
    if (fileDialog->exec() == QDialog::Accepted) {
        auto fileName = fileDialog->selectedFiles().first();
        controller_->SaveImage(fileName);
    }
}

QStringList s21::SaveImageCommand::GetSupportedImageTypes() {
    QStringList types;
    const auto supportedTypes = QImageReader::supportedMimeTypes();
    for (const QByteArray& name : supportedTypes) {
        if (name == "image/bmp" || name == "image/jpeg") types.append(name);
    }
    return types;
}

void s21::StartRecordGifCommand::Execute() {
    controller_->StartRecordGif();
    controller_->AddFrameToGif();
}

void s21::StopRecordGifCommand::Execute() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"),
                           QString(),
                           QObject::tr("*.gif"));
    if (!fileName.isEmpty())
        controller_->SaveGif(fileName);
}

void s21::CloseFileCommand::Execute() { controller_->RemoveFigure(figure_index_); }

void s21::OpenSettingsWindowCommand::Execute() {
    window_->setValues(controller_->objectSettings());
    window_->show();
}

void s21::SaveSettingsCommand::Execute() {
    controller_->SaveSettings(objSettings_);
    controller_->UpdateSettingsInDrawer();
}

void s21::TransformSceneCommand::Execute() {
    controller_->Transform(point_, action_);
}
