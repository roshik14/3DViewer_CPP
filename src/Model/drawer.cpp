#include "drawer.h"

#include <QDrag>
#include <QFile>
#include <QMatrix4x4>
#include <QTime>
#include <QTimer>
#include <QVector3D>
#include <QWheelEvent>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
using s21::Drawer;
using s21::Point;

Drawer::Drawer(QWidget* parent) : QOpenGLWidget(parent), settings_(ObjectSettings{}) {}

void Drawer::initializeGL() {
    initializeOpenGLFunctions();

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    ReadShaderFromFile(&vertexShaderId, ":/shaders/shaders/vs.glsl");
    ReadShaderFromFile(&fragmentShaderId, ":/shaders/shaders/fs.glsl");

    CreateProgramWithShaders(vertexShaderId, fragmentShaderId);

    MatrixID = glGetUniformLocation(program, "MVP");
    attributeCoord3d = glGetAttribLocation(program, "coord3d");
    color_location = glGetUniformLocation(program, "color");

    View.setToIdentity();
    View.lookAt(QVector3D(15, 15, 15), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    SetPerspective(width(), height());
}

void Drawer::ReadShaderFromFile(GLuint *shaderId, const char* pathToShader) {
    QFile shaderFile(pathToShader);
    if (shaderFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream inputFileStream(&shaderFile);
        QByteArray byteArray = inputFileStream.readAll().toLocal8Bit();
        char const* sourceCodePointer = byteArray.data();
        shaderFile.close();
        glShaderSource(*shaderId, 1, &sourceCodePointer, NULL);
        glCompileShader(*shaderId);
    }
}

void Drawer::CreateProgramWithShaders(GLuint vertexShaderId, GLuint fragmentShaderId) {
    program = glCreateProgram();
    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);
}

void Drawer::CreateBuffer(GLuint* bufferID) {
    glGenBuffers(1, bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, *bufferID);
}

void Drawer::resizeGL(int w, int h) {
    SetPerspective(w, h);
    glViewport(0, 0, w, h);
}

QMatrix4x4 Drawer::CreateMVPMatrix() {
    SetPerspective(width(), height());
    QMatrix4x4 Model;
    return Projection * View * Model;
}

void Drawer::SetColor() {
    colorVertex[0] = settings_.vertexColor.red() / 255.0;
    colorVertex[1] = settings_.vertexColor.green() / 255.0;
    colorVertex[2] = settings_.vertexColor.blue() / 255.0;
    colorEdges[0] = settings_.edgeColor.red() / 255.0;
    colorEdges[1] = settings_.edgeColor.green() / 255.0;
    colorEdges[2] = settings_.edgeColor.blue() / 255.0;
}

void Drawer::UpdateSettings() {
    perspective = settings_.projectionType;

    glClearColor(settings_.backgroundColor.red() / 255.0, settings_.backgroundColor.green() / 255.0,
                 settings_.backgroundColor.blue() / 255.0, settings_.backgroundColor.alpha() / 255.0);

    SetColor();

    glPointSize(settings_.vertexSize);
    glLineWidth(settings_.edgeSize);

    if (settings_.vertexType == 1) {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glDisable(GL_POINT_SMOOTH);
    } else if (settings_.vertexType == 2) {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
    } else {
        glPointSize(0.1);
    }

    if (settings_.lineType == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xff);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Drawer::paintGL() {
    UpdateSettings();
    glUseProgram(program);

    QMatrix4x4 MVP = CreateMVPMatrix();
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP(0, 0));

    CreateBuffer(&vertexBufferObject);
    ConnectVectorWithBuffer(vertices_, attributeCoord3d);

    DrawModel();

    glDisableVertexAttribArray(attributeCoord3d);

    doneCurrent();
}

void Drawer::ConnectVectorWithBuffer(std::vector<Point> vertices, GLuint attribute) {
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    if (vertices.size()) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, vertices.data(), GL_STATIC_DRAW);
    }
}

void Drawer::DrawModel() {
    if (indices_.size()) {
        for (size_t i = 0; i < indices_.size(); ++i) {
            glUniform3fv(color_location, 1, colorEdges);
            glDrawElements(GL_LINE_LOOP, indices_[i].size(), GL_UNSIGNED_INT, indices_[i].data());
            glUniform3fv(color_location, 1, colorVertex);
            glDrawElements(GL_POINTS, indices_[i].size(), GL_UNSIGNED_INT, indices_[i].data());
        }
    }
}

void Drawer::wheelEvent(QWheelEvent* event) {
    QPoint numPixels = event->pixelDelta();
    if (numPixels.y() > 0) {
        View.scale(1.1);
    } else if (numPixels.y() < 0) {
        View.scale(0.9);
    }
    update();
}

void Drawer::mousePressEvent(QMouseEvent* event) {
    mousePressPosition = QVector2D(event->position());
    dragged = true;
}

void Drawer::mouseMoveEvent(QMouseEvent* event) {
    QVector2D diff = QVector2D(event->position()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), -diff.x(), 0.0).normalized();
    if (dragged) {
        View.rotate(5, n);
    }
    mousePressPosition = QVector2D(event->position());
    update();
}

void Drawer::mouseReleaseEvent(QMouseEvent* event) { dragged = false; }

int Drawer::CountDigits(float n) { return floor(log10(static_cast<int>(n)) + 1); }

void Drawer::SetVertices(std::vector<Point>&& vertices)  noexcept { vertices_ = std::move(vertices); }

void Drawer::SetIndices(std::vector<std::vector<int>>&& indices) noexcept { indices_ = std::move(indices); }

void Drawer::UpdateScreen() { update(); }


void Drawer::SetPerspective(float w, float h) {
    Projection.setToIdentity();
    if (perspective) {
        float aspect = h / w;
        Projection.ortho(-45.0, 45.0, -45.0 * aspect, 45.0 * aspect, 0.1, 100);
    } else {
        qreal aspect = qreal(w) / qreal(h ? h : 1);
        const qreal zNear = 0.1, zFar = 100.0, fov = 45.0;
        Projection.setToIdentity();
        Projection.perspective(fov, aspect, zNear, zFar);
    }
}

void Drawer::SetSettings(const ObjectSettings& settings) { settings_ = settings; }
