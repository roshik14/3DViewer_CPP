#include <QApplication>

#include "Controller/controller.h"
#include "Model/facade_model.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::FacadeModel facade;
    s21::Controller controller(&facade);
    s21::MainWindow w(&controller);
    w.show();
    return a.exec();
}
