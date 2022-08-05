QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/Model/s21_matrix_oop.cpp \
    ../src/Model/affine_strategy.cpp \
    ../src/Model/figure.cpp \
    ../src/Model/scene.cpp \
    ../src/Model/file_reader.cpp \
    ../src/Model/gif_maker.cpp \
    ../src/Model/drawer.cpp \
    ../src/Model/facade_model.cpp \
    ../src/Controller/controller.cpp \
    ../src/settingswindow.cpp \
    ../src/command.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \

HEADERS += \
    ../src/Model/affine_strategy.h \
    ../src/Model/surface.h \
    ../src/Model/figure.h \
    ../src/Model/scene.h \
    ../src/Model/s21_matrix_oop.h \
    ../src/Model/file_reader.h \
    ../src/Model/settings.h \
    ../src/Model/gif_maker.h \
    ../src/Model/drawer.h \
    ../src/Model/facade_model.h \
    ../src/Controller/controller.h \
    ../src/object_settings.h \
    ../src/settingswindow.h \
    ../src/command.h \
    ../src/point.h \
    ../src/enums.h \
    ../src/mainwindow.h \

FORMS += \
    ../src/mainwindow.ui \
    ../src/settingswindow.ui

include(3rdparty/QtGifImageLib/gifimage/qtgifimage.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    ../src/icons.qrc \
    ../src/shaders.qrc
