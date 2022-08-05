#ifndef SRC_COMMAND_H_
#define SRC_COMMAND_H_
#include "Controller/controller.h"
#include "enums.h"
#include "settingswindow.h"

namespace s21 {
class Command {
 public:
    virtual void Execute() = 0;
    virtual ~Command() {}

 protected:
    Controller *controller_;
    explicit Command(Controller *controller) : controller_(controller) {}
};

class OpenFileCommand : public Command {
 public:
    explicit OpenFileCommand(Controller *controller) : Command(controller) {}
    void Execute() override;
};

class SaveImageCommand : public Command {
 public:
    SaveImageCommand(Controller *controller, QWidget *parent)
        : Command(controller), parent_(parent) {}
    void Execute() override;
 private:
    QWidget *parent_;
    QStringList GetSupportedImageTypes();
};

class StartRecordGifCommand : public Command {
 public:
    explicit StartRecordGifCommand(Controller *controller) : Command(controller) {}
    void Execute() override;
};

class StopRecordGifCommand : public Command {
 public:
    explicit StopRecordGifCommand(Controller *controller) : Command(controller) {}
    void Execute() override;
};

class CloseFileCommand : public Command {
 public:
    CloseFileCommand(Controller *controller, int figure_index)
        : Command(controller), figure_index_(figure_index) {}
    void Execute() override;
 private:
    int figure_index_;
};

class OpenSettingsWindowCommand : public Command {
 public:
    OpenSettingsWindowCommand(Controller *controller, std::shared_ptr<SettingsWindow> window)
        : Command(controller), window_(window) {}
    void Execute() override;
 private:
    std::shared_ptr<SettingsWindow> window_;
};

class SaveSettingsCommand : public Command {
 public:
    SaveSettingsCommand(Controller *controller, const ObjectSettings &objSettings)
        : Command(controller), objSettings_(objSettings) {}
    void Execute() override;
 private:
    ObjectSettings objSettings_;
};

class TransformSceneCommand : public Command {
 public:
    TransformSceneCommand(Controller *controller, const Point &p, SceneAction action)
        : Command(controller), point_(p), action_(action) {}
    void Execute() override;

 private:
    const Point point_;
    SceneAction action_;
};

}  // namespace s21

#endif  // SRC_COMMAND_H_
